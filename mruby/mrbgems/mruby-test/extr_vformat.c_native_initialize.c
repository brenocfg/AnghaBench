#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_3__ {int type; int d; char* s; int /*<<< orphan*/  C; int /*<<< orphan*/  n; scalar_t__ i; int /*<<< orphan*/  f; int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ VFNative ;
typedef  int VFArgumentType ;

/* Variables and functions */
#define  ARG_C 134 
#define  ARG_c 133 
#define  ARG_d 132 
#define  ARG_f 131 
#define  ARG_i 130 
#define  ARG_n 129 
#define  ARG_s 128 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 size_t RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_data_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_float (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  native_data_type ; 

__attribute__((used)) static mrb_value
native_initialize(mrb_state *mrb, mrb_value self)
{
  VFNative data, *datap;
  mrb_int type;
  mrb_value obj;

  mrb_get_args(mrb, "io", &type, &obj);
  data.type = (VFArgumentType)type;
  switch (data.type) {
    case ARG_c: data.c = RSTRING_PTR(obj)[0]; break;
    case ARG_d: data.d = (int)mrb_fixnum(obj); break;
    case ARG_f: data.f = mrb_float(obj); break;
    case ARG_i: data.i = mrb_fixnum(obj); break;
/*    case ARG_l: data.l = (size_t)mrb_fixnum(obj); break;*/
    case ARG_n: data.n = mrb_symbol(obj); break;
    case ARG_s: data.s = (char*)mrb_malloc(mrb, RSTRING_LEN(obj) + 1);
                memcpy(data.s, RSTRING_PTR(obj), RSTRING_LEN(obj));
                data.s[RSTRING_LEN(obj)] = '\0'; break;
    case ARG_C: data.C = mrb_class_ptr(obj); break;
    default: mrb_raise(mrb, E_ARGUMENT_ERROR, "unknown type");
  }
  datap = (VFNative*)mrb_malloc(mrb, sizeof(VFNative));
  *datap = data;
  mrb_data_init(self, datap, &native_data_type);
  return self;
}