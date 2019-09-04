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
typedef  enum iscsi_error_types { ____Placeholder_iscsi_error_types } iscsi_error_types ;
struct TYPE_3__ {int error_code; char* err_string; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* qedi_iscsi_error ; 

char *qedi_get_iscsi_error(enum iscsi_error_types err_code)
{
	int i;
	char *msg = NULL;

	for (i = 0; i < ARRAY_SIZE(qedi_iscsi_error); i++) {
		if (qedi_iscsi_error[i].error_code == err_code) {
			msg = qedi_iscsi_error[i].err_string;
			break;
		}
	}
	return msg;
}