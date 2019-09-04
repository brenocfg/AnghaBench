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
struct lwtunnel_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct lwtunnel_state* kzalloc (int,int /*<<< orphan*/ ) ; 

struct lwtunnel_state *lwtunnel_state_alloc(int encap_len)
{
	struct lwtunnel_state *lws;

	lws = kzalloc(sizeof(*lws) + encap_len, GFP_ATOMIC);

	return lws;
}