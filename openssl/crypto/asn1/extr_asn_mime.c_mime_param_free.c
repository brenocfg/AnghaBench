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
struct TYPE_4__ {struct TYPE_4__* param_value; struct TYPE_4__* param_name; } ;
typedef  TYPE_1__ MIME_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 

__attribute__((used)) static void mime_param_free(MIME_PARAM *param)
{
    OPENSSL_free(param->param_name);
    OPENSSL_free(param->param_value);
    OPENSSL_free(param);
}