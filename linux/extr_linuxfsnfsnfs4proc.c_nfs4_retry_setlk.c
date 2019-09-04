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
struct nfs4_state {int dummy; } ;
struct file_lock {int dummy; } ;

/* Variables and functions */
 int nfs4_retry_setlk_simple (struct nfs4_state*,int,struct file_lock*) ; 

__attribute__((used)) static inline int
nfs4_retry_setlk(struct nfs4_state *state, int cmd, struct file_lock *request)
{
	return nfs4_retry_setlk_simple(state, cmd, request);
}