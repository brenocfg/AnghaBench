#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int ONSTACK_ALLOC_MAX ; 
 size_t ONSTACK_STRLEN_MAX ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_intern (int /*<<< orphan*/ *,char*,size_t) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,size_t) ; 
 char* mrb_sym_name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static mrb_sym
mrb_id_attrset(mrb_state *mrb, mrb_sym id)
{
#define ONSTACK_ALLOC_MAX 32
#define ONSTACK_STRLEN_MAX (ONSTACK_ALLOC_MAX - 1) /* '=' character */

  const char *name;
  char *buf;
  mrb_int len;
  mrb_sym mid;
  char onstack[ONSTACK_ALLOC_MAX];

  name = mrb_sym_name_len(mrb, id, &len);
  if (len > ONSTACK_STRLEN_MAX) {
    buf = (char *)mrb_malloc(mrb, (size_t)len+1);
  }
  else {
    buf = onstack;
  }
  memcpy(buf, name, (size_t)len);
  buf[len] = '=';

  mid = mrb_intern(mrb, buf, len+1);
  if (buf != onstack) {
    mrb_free(mrb, buf);
  }
  return mid;
}