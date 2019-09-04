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
typedef  int /*<<< orphan*/  zend_off_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  cdf_secid_t ;
typedef  int /*<<< orphan*/  cdf_info_t ;
typedef  int /*<<< orphan*/  cdf_header_t ;

/* Variables and functions */
 size_t CDF_SEC_POS (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 size_t CDF_SEC_SIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cdf_read (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char*,size_t) ; 

ssize_t
cdf_read_sector(const cdf_info_t *info, void *buf, size_t offs, size_t len,
    const cdf_header_t *h, cdf_secid_t id)
{
	size_t pos = CDF_SEC_POS(h, id);
	assert(CDF_SEC_SIZE(h) == len);
	return cdf_read(info, (zend_off_t)pos, ((char *)buf) + offs, len);
}