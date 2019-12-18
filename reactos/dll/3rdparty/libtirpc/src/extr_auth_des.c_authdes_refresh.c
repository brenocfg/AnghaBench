#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  key; } ;
struct authdes_cred {TYPE_1__ adc_fullname; int /*<<< orphan*/  adc_namekind; } ;
struct ad_private {int /*<<< orphan*/  ad_fullname; int /*<<< orphan*/  ad_xkey; int /*<<< orphan*/  ad_servername; scalar_t__ ad_pkey; scalar_t__ ad_dosync; int /*<<< orphan*/  ad_netid; int /*<<< orphan*/  ad_uaddr; int /*<<< orphan*/  ad_timehost; int /*<<< orphan*/  ad_nis_srvr; int /*<<< orphan*/  ad_timediff; struct authdes_cred ad_cred; } ;
struct TYPE_8__ {char* n_bytes; scalar_t__ n_len; } ;
typedef  TYPE_2__ netobj ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_9__ {int /*<<< orphan*/  ah_key; } ;
typedef  TYPE_3__ AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  ADN_FULLNAME ; 
 struct ad_private* AUTH_PRIVATE (TYPE_3__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int __rpc_get_time_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ key_encryptsession_pk (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static bool_t
authdes_refresh(AUTH *auth, void *dummy)
{
/* LINTED pointer alignment */
	struct ad_private *ad = AUTH_PRIVATE(auth);
	struct authdes_cred *cred = &ad->ad_cred;
	int		ok;
	netobj		pkey;

	if (ad->ad_dosync) {
#if 1 // WINDOWS
		ok = 1;
#else
                ok = __rpc_get_time_offset(&ad->ad_timediff, ad->ad_nis_srvr,
		    ad->ad_timehost, &(ad->ad_uaddr),
		    &(ad->ad_netid));
#endif
		if (! ok) {
			/*
			 * Hope the clocks are synced!
			 */
			ad->ad_dosync = 0;
			//syslog(LOG_DEBUG,
			//    "authdes_refresh: unable to synchronize clock");
		 }
	}
	ad->ad_xkey = auth->ah_key;
	pkey.n_bytes = (char *)(ad->ad_pkey);
	pkey.n_len = (u_int)strlen((char *)ad->ad_pkey) + 1;
	if (key_encryptsession_pk(ad->ad_servername, &pkey, &ad->ad_xkey) < 0) {
		//syslog(LOG_INFO,
		//    "authdes_refresh: keyserv(1m) is unable to encrypt session key");
		return (FALSE);
	}
	cred->adc_fullname.key = ad->ad_xkey;
	cred->adc_namekind = ADN_FULLNAME;
	cred->adc_fullname.name = ad->ad_fullname;
	return (TRUE);
}