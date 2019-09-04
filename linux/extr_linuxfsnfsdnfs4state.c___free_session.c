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
struct nfsd4_session {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_session_slots (struct nfsd4_session*) ; 
 int /*<<< orphan*/  kfree (struct nfsd4_session*) ; 

__attribute__((used)) static void __free_session(struct nfsd4_session *ses)
{
	free_session_slots(ses);
	kfree(ses);
}