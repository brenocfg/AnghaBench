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
struct cxgbi_sock {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CTP_ACTIVE_CLOSE ; 

__attribute__((used)) static inline int cxgbi_sock_is_closing(struct cxgbi_sock *csk)
{
	return csk->state >= CTP_ACTIVE_CLOSE;
}