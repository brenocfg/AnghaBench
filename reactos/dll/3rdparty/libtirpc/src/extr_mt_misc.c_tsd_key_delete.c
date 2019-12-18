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

/* Variables and functions */
 int clnt_broadcast_key ; 
 int nc_key ; 
 int rce_key ; 
 int rpc_call_key ; 
 int tcp_key ; 
 int /*<<< orphan*/  thr_keydelete (int) ; 
 int udp_key ; 

void tsd_key_delete(void)
{
	if (clnt_broadcast_key != -1)
		thr_keydelete(clnt_broadcast_key);
	if (rpc_call_key != -1)
		thr_keydelete(rpc_call_key);
	if (tcp_key != -1)
		thr_keydelete(tcp_key);
	if (udp_key != -1)
		thr_keydelete(udp_key);
	if (nc_key != -1)
		thr_keydelete(nc_key);
	if (rce_key != -1)
		thr_keydelete(rce_key);
	return;
}