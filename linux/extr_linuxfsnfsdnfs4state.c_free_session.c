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
struct nfsd4_session {int /*<<< orphan*/  se_fchannel; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_session (struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_del_conns (struct nfsd4_session*) ; 
 int /*<<< orphan*/  nfsd4_put_drc_mem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_session(struct nfsd4_session *ses)
{
	nfsd4_del_conns(ses);
	nfsd4_put_drc_mem(&ses->se_fchannel);
	__free_session(ses);
}