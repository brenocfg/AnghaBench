#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct RString* fshared; } ;
struct TYPE_5__ {TYPE_1__ aux; int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; } ;
struct TYPE_6__ {TYPE_2__ heap; } ;
struct RString {TYPE_3__ as; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSHARED ; 
 int /*<<< orphan*/  RSTR_SET_TYPE_FLAG (struct RString*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RString*
str_init_fshared(const struct RString *orig, struct RString *s, struct RString *fshared)
{
  s->as.heap.ptr = orig->as.heap.ptr;
  s->as.heap.len = orig->as.heap.len;
  s->as.heap.aux.fshared = fshared;
  RSTR_SET_TYPE_FLAG(s, FSHARED);
  return s;
}