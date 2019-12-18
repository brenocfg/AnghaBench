#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_3__ {char* key; int frametype; } ;
typedef  TYPE_1__ typekey_t ;
struct TYPE_4__ {char* name; scalar_t__ frametype; } ;
typedef  TYPE_2__ field_t ;

/* Variables and functions */
 scalar_t__ ANY_FRAME ; 
 int htonl (int) ; 
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int comparator(const void *typekey, const void *obj) {
  field_t *f = (field_t *) obj;
  const char *name = f->name;
  const typekey_t *tk = (const typekey_t *) typekey;
  const char *key = tk->key;

  if (!((uint32)key & 3) && !((uint32)name & 3)) {
    // Since all strings are 3 characters or more, can do accelerated first comparison
    uint32 key32 = htonl(*(uint32 *) key);
    uint32 name32 = htonl(*(uint32 *) name);

    if (key32 < name32) {
      return -1;
    }
    if (key32 > name32) {
      return 1;
    }
  }

  int rc = strcmp((const char *) key, name);
  if (rc) {
    return rc;
  }

  if (f->frametype == ANY_FRAME) {
    return 0;
  }

  return tk->frametype - f->frametype;
}