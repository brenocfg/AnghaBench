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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  MRB_TT_CLASS 130 
#define  MRB_TT_MODULE 129 
#define  MRB_TT_SCLASS 128 
 int /*<<< orphan*/  TRUE ; 
 int mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
class_ptr_p(mrb_value obj)
{
  switch (mrb_type(obj)) {
  case MRB_TT_CLASS:
  case MRB_TT_SCLASS:
  case MRB_TT_MODULE:
    return TRUE;
  default:
    return FALSE;
  }
}