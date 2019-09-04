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
struct sk_msg_buff {scalar_t__ sk_redir; } ;

/* Variables and functions */
 int SK_PASS ; 
 int __SK_DROP ; 
 int __SK_PASS ; 
 int __SK_REDIRECT ; 

__attribute__((used)) static int bpf_map_msg_verdict(int _rc, struct sk_msg_buff *md)
{
	return ((_rc == SK_PASS) ?
	       (md->sk_redir ? __SK_REDIRECT : __SK_PASS) :
	       __SK_DROP);
}