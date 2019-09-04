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
struct cs_etm_decoder {int /*<<< orphan*/  (* packet_printer ) (char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (char const*) ; 

__attribute__((used)) static void cs_etm_decoder__print_str_cb(const void *p_context,
					 const char *msg,
					 const int str_len)
{
	if (p_context && str_len)
		((struct cs_etm_decoder *)p_context)->packet_printer(msg);
}