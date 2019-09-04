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
typedef  int /*<<< orphan*/  u8 ;
struct rfcomm_session {int dummy; } ;
struct rfcomm_dlc {int dummy; } ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rfcomm_dlc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __dlci (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __session_dir (struct rfcomm_session*) ; 
 scalar_t__ rfcomm_check_channel (int /*<<< orphan*/ ) ; 
 struct rfcomm_dlc* rfcomm_dlc_get (struct rfcomm_session*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_lock () ; 
 struct rfcomm_session* rfcomm_session_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_unlock () ; 

struct rfcomm_dlc *rfcomm_dlc_exists(bdaddr_t *src, bdaddr_t *dst, u8 channel)
{
	struct rfcomm_session *s;
	struct rfcomm_dlc *dlc = NULL;
	u8 dlci;

	if (rfcomm_check_channel(channel))
		return ERR_PTR(-EINVAL);

	rfcomm_lock();
	s = rfcomm_session_get(src, dst);
	if (s) {
		dlci = __dlci(__session_dir(s), channel);
		dlc = rfcomm_dlc_get(s, dlci);
	}
	rfcomm_unlock();
	return dlc;
}