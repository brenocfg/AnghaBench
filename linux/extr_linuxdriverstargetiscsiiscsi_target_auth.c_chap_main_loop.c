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
typedef  int u32 ;
struct iscsi_node_auth {scalar_t__ authenticate_target; } ;
struct iscsi_conn {struct iscsi_chap* auth_protocol; } ;
struct iscsi_chap {scalar_t__ chap_state; } ;

/* Variables and functions */
 scalar_t__ CHAP_STAGE_SERVER_AIC ; 
 scalar_t__ CHAP_STAGE_SERVER_NR ; 
 int /*<<< orphan*/  chap_close (struct iscsi_conn*) ; 
 scalar_t__ chap_got_response (struct iscsi_conn*,struct iscsi_node_auth*,char*,char*,int*) ; 
 struct iscsi_chap* chap_server_open (struct iscsi_conn*,struct iscsi_node_auth*,char*,char*,int*) ; 
 int /*<<< orphan*/  convert_null_to_semi (char*,int) ; 

u32 chap_main_loop(
	struct iscsi_conn *conn,
	struct iscsi_node_auth *auth,
	char *in_text,
	char *out_text,
	int *in_len,
	int *out_len)
{
	struct iscsi_chap *chap = conn->auth_protocol;

	if (!chap) {
		chap = chap_server_open(conn, auth, in_text, out_text, out_len);
		if (!chap)
			return 2;
		chap->chap_state = CHAP_STAGE_SERVER_AIC;
		return 0;
	} else if (chap->chap_state == CHAP_STAGE_SERVER_AIC) {
		convert_null_to_semi(in_text, *in_len);
		if (chap_got_response(conn, auth, in_text, out_text,
				out_len) < 0) {
			chap_close(conn);
			return 2;
		}
		if (auth->authenticate_target)
			chap->chap_state = CHAP_STAGE_SERVER_NR;
		else
			*out_len = 0;
		chap_close(conn);
		return 1;
	}

	return 2;
}