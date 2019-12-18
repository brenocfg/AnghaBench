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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct nfnl_callback {int dummy; } ;
struct nfnetlink_subsystem {size_t cb_count; struct nfnl_callback const* cb; } ;

/* Variables and functions */
 size_t NFNL_MSG_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const struct nfnl_callback *
nfnetlink_find_client(u16 type, const struct nfnetlink_subsystem *ss)
{
	u8 cb_id = NFNL_MSG_TYPE(type);

	if (cb_id >= ss->cb_count)
		return NULL;

	return &ss->cb[cb_id];
}