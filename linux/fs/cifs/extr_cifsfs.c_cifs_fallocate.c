#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct cifs_tcon {TYPE_1__* ses; } ;
struct cifs_sb_info {int dummy; } ;
struct TCP_Server_Info {TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_4__ {long (* fallocate ) (struct file*,struct cifs_tcon*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {struct TCP_Server_Info* server; } ;

/* Variables and functions */
 struct cifs_sb_info* CIFS_FILE_SB (struct file*) ; 
 long EOPNOTSUPP ; 
 struct cifs_tcon* cifs_sb_master_tcon (struct cifs_sb_info*) ; 
 long stub1 (struct file*,struct cifs_tcon*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long cifs_fallocate(struct file *file, int mode, loff_t off, loff_t len)
{
	struct cifs_sb_info *cifs_sb = CIFS_FILE_SB(file);
	struct cifs_tcon *tcon = cifs_sb_master_tcon(cifs_sb);
	struct TCP_Server_Info *server = tcon->ses->server;

	if (server->ops->fallocate)
		return server->ops->fallocate(file, tcon, mode, off, len);

	return -EOPNOTSUPP;
}