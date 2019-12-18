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
struct nfsd4_session {int se_flags; } ;

/* Variables and functions */
 int NFS4_SESSION_DEAD ; 

__attribute__((used)) static bool is_session_dead(struct nfsd4_session *ses)
{
	return ses->se_flags & NFS4_SESSION_DEAD;
}