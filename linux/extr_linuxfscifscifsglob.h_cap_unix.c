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
struct cifs_ses {int capabilities; TYPE_2__* server; } ;
struct TYPE_4__ {TYPE_1__* vals; } ;
struct TYPE_3__ {int cap_unix; } ;

/* Variables and functions */

__attribute__((used)) static inline bool
cap_unix(struct cifs_ses *ses)
{
	return ses->server->vals->cap_unix & ses->capabilities;
}