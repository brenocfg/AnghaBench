#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sess_data {struct cifs_ses* ses; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  response; } ;
struct cifs_ses {int need_reconnect; int /*<<< orphan*/  status; TYPE_3__* server; TYPE_2__ auth_key; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; int /*<<< orphan*/  response; } ;
struct TYPE_6__ {int session_estab; int sequence_number; int /*<<< orphan*/  srv_mutex; TYPE_1__ session_key; scalar_t__ sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  CifsGood ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FYI ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GlobalMid_Lock ; 
 int /*<<< orphan*/  cifs_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sess_establish_session(struct sess_data *sess_data)
{
	struct cifs_ses *ses = sess_data->ses;

	mutex_lock(&ses->server->srv_mutex);
	if (!ses->server->session_estab) {
		if (ses->server->sign) {
			ses->server->session_key.response =
				kmemdup(ses->auth_key.response,
				ses->auth_key.len, GFP_KERNEL);
			if (!ses->server->session_key.response) {
				mutex_unlock(&ses->server->srv_mutex);
				return -ENOMEM;
			}
			ses->server->session_key.len =
						ses->auth_key.len;
		}
		ses->server->sequence_number = 0x2;
		ses->server->session_estab = true;
	}
	mutex_unlock(&ses->server->srv_mutex);

	cifs_dbg(FYI, "CIFS session established successfully\n");
	spin_lock(&GlobalMid_Lock);
	ses->status = CifsGood;
	ses->need_reconnect = false;
	spin_unlock(&GlobalMid_Lock);

	return 0;
}