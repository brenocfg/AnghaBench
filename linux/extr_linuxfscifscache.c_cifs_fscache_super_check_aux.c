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
typedef  int uint16_t ;
struct cifs_tcon {int /*<<< orphan*/  resource_id; } ;
struct cifs_fscache_super_auxdata {int /*<<< orphan*/  resource_id; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  enum fscache_checkaux { ____Placeholder_fscache_checkaux } fscache_checkaux ;
typedef  int /*<<< orphan*/  auxdata ;

/* Variables and functions */
 int FSCACHE_CHECKAUX_OBSOLETE ; 
 int FSCACHE_CHECKAUX_OKAY ; 
 scalar_t__ memcmp (void const*,struct cifs_fscache_super_auxdata*,int) ; 
 int /*<<< orphan*/  memset (struct cifs_fscache_super_auxdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum
fscache_checkaux cifs_fscache_super_check_aux(void *cookie_netfs_data,
					      const void *data,
					      uint16_t datalen,
					      loff_t object_size)
{
	struct cifs_fscache_super_auxdata auxdata;
	const struct cifs_tcon *tcon = cookie_netfs_data;

	if (datalen != sizeof(auxdata))
		return FSCACHE_CHECKAUX_OBSOLETE;

	memset(&auxdata, 0, sizeof(auxdata));
	auxdata.resource_id = tcon->resource_id;

	if (memcmp(data, &auxdata, datalen) != 0)
		return FSCACHE_CHECKAUX_OBSOLETE;

	return FSCACHE_CHECKAUX_OKAY;
}