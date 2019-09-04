#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  error_text; } ;
struct TYPE_5__ {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ outputs; int /*<<< orphan*/  want_errortext; TYPE_1__ inputs; } ;
typedef  TYPE_3__ php_stream_xport_param ;

/* Variables and functions */
 char* parse_ip_address_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline char *parse_ip_address(php_stream_xport_param *xparam, int *portno)
{
	return parse_ip_address_ex(xparam->inputs.name, xparam->inputs.namelen, portno, xparam->want_errortext, &xparam->outputs.error_text);
}