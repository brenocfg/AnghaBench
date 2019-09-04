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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  route_hi; int /*<<< orphan*/  route_lo; } ;
struct tb_switch {int /*<<< orphan*/  connection_id; TYPE_1__ config; int /*<<< orphan*/  const* uuid; } ;
struct tb {int dummy; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  code; } ;
struct icm_tr_pkg_challenge_device_response {int /*<<< orphan*/  const* response; TYPE_2__ hdr; int /*<<< orphan*/ * challenge; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  route_hi; int /*<<< orphan*/  route_lo; int /*<<< orphan*/  ep_uuid; } ;
struct icm_tr_pkg_challenge_device {int /*<<< orphan*/  const* response; TYPE_2__ hdr; int /*<<< orphan*/ * challenge; int /*<<< orphan*/  connection_id; int /*<<< orphan*/  route_hi; int /*<<< orphan*/  route_lo; int /*<<< orphan*/  ep_uuid; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int EKEYREJECTED ; 
 int ENOKEY ; 
 int /*<<< orphan*/  ICM_CHALLENGE_DEVICE ; 
 int ICM_FLAGS_ERROR ; 
 int ICM_FLAGS_NO_KEY ; 
 int /*<<< orphan*/  ICM_TIMEOUT ; 
 int TB_SWITCH_KEY_SIZE ; 
 int icm_request (struct tb*,struct icm_tr_pkg_challenge_device_response*,int,struct icm_tr_pkg_challenge_device_response*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct icm_tr_pkg_challenge_device_response*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int icm_tr_challenge_switch_key(struct tb *tb, struct tb_switch *sw,
				       const u8 *challenge, u8 *response)
{
	struct icm_tr_pkg_challenge_device_response reply;
	struct icm_tr_pkg_challenge_device request;
	int ret;

	memset(&request, 0, sizeof(request));
	memcpy(&request.ep_uuid, sw->uuid, sizeof(request.ep_uuid));
	request.hdr.code = ICM_CHALLENGE_DEVICE;
	request.route_lo = sw->config.route_lo;
	request.route_hi = sw->config.route_hi;
	request.connection_id = sw->connection_id;
	memcpy(request.challenge, challenge, TB_SWITCH_KEY_SIZE);

	memset(&reply, 0, sizeof(reply));
	ret = icm_request(tb, &request, sizeof(request), &reply, sizeof(reply),
			  1, ICM_TIMEOUT);
	if (ret)
		return ret;

	if (reply.hdr.flags & ICM_FLAGS_ERROR)
		return -EKEYREJECTED;
	if (reply.hdr.flags & ICM_FLAGS_NO_KEY)
		return -ENOKEY;

	memcpy(response, reply.response, TB_SWITCH_KEY_SIZE);

	return 0;
}