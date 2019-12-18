#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned char* s; } ;
typedef  TYPE_1__ str ;

/* Variables and functions */
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

str * coap_new_string(size_t size) {
  str *s = (str *)malloc(sizeof(str) + size + 1);
  if ( !s ) {
    return NULL;
  }

  memset(s, 0, sizeof(str));
  s->s = ((unsigned char *)s) + sizeof(str);
  return s;
}