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
struct cifs_ses {int dummy; } ;
struct TCP_Server_Info {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  cifs_tcp_ses_lock ; 
 struct cifs_ses* smb2_find_smb_ses_unlocked (struct TCP_Server_Info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct cifs_ses *
smb2_find_smb_ses(struct TCP_Server_Info *server, __u64 ses_id)
{
	struct cifs_ses *ses;

	spin_lock(&cifs_tcp_ses_lock);
	ses = smb2_find_smb_ses_unlocked(server, ses_id);
	spin_unlock(&cifs_tcp_ses_lock);

	return ses;
}