#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  data; } ;
struct TYPE_9__ {TYPE_1__ env; } ;
struct TYPE_10__ {TYPE_2__ pkt; } ;
struct TYPE_11__ {TYPE_3__ tran; } ;
typedef  TYPE_4__ libqnxr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSMSG_ENV_ADDARG ; 
 int DS_DATA_MAX_SIZE ; 
 int /*<<< orphan*/  DStMsg_env ; 
 int /*<<< orphan*/  DStMsg_env_t ; 
 int /*<<< orphan*/  SET_CHANNEL_DEBUG ; 
 int /*<<< orphan*/  data ; 
 int /*<<< orphan*/  eprintf (char*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int nto_send (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  nto_send_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

int nto_send_arg (libqnxr_t *g, const char *arg) {
	int len;

	if (!g) return 0;

	len = strlen (arg) + 1;
	if (len > DS_DATA_MAX_SIZE) {
		eprintf ("Argument too long: %.40s...\n", arg);
		return 0;
	}
	nto_send_init (g, DStMsg_env, DSMSG_ENV_ADDARG, SET_CHANNEL_DEBUG);
	memcpy (g->tran.pkt.env.data, arg, len);
	return nto_send (g, offsetof (DStMsg_env_t, data) + len, 1);
}