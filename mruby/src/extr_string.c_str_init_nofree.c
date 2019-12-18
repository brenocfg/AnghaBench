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
struct TYPE_4__ {scalar_t__ capa; } ;
struct TYPE_5__ {char* ptr; TYPE_1__ aux; scalar_t__ len; } ;
struct TYPE_6__ {TYPE_2__ heap; } ;
struct RString {TYPE_3__ as; } ;
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  NOFREE ; 
 int /*<<< orphan*/  RSTR_SET_TYPE_FLAG (struct RString*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct RString*
str_init_nofree(struct RString *s, const char *p, size_t len)
{
  s->as.heap.ptr = (char *)p;
  s->as.heap.len = (mrb_int)len;
  s->as.heap.aux.capa = 0;             /* nofree */
  RSTR_SET_TYPE_FLAG(s, NOFREE);
  return s;
}