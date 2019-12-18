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
struct ncsi_package {int dummy; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCSI_CHANNEL_INDEX (unsigned char) ; 
 int /*<<< orphan*/  NCSI_PACKAGE_INDEX (unsigned char) ; 
 struct ncsi_channel* ncsi_find_channel (struct ncsi_package*,int /*<<< orphan*/ ) ; 
 struct ncsi_package* ncsi_find_package (struct ncsi_dev_priv*,int /*<<< orphan*/ ) ; 

void ncsi_find_package_and_channel(struct ncsi_dev_priv *ndp,
				   unsigned char id,
				   struct ncsi_package **np,
				   struct ncsi_channel **nc)
{
	struct ncsi_package *p;
	struct ncsi_channel *c;

	p = ncsi_find_package(ndp, NCSI_PACKAGE_INDEX(id));
	c = p ? ncsi_find_channel(p, NCSI_CHANNEL_INDEX(id)) : NULL;

	if (np)
		*np = p;
	if (nc)
		*nc = c;
}