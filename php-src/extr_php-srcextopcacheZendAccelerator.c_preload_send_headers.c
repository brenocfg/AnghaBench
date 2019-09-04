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
typedef  int /*<<< orphan*/  sapi_headers_struct ;

/* Variables and functions */
 int SAPI_HEADER_SENT_SUCCESSFULLY ; 

__attribute__((used)) static int preload_send_headers(sapi_headers_struct *sapi_headers)
{
	return SAPI_HEADER_SENT_SUCCESSFULLY;
}