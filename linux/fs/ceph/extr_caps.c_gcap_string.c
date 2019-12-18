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

/* Variables and functions */
 int CEPH_CAP_GBUFFER ; 
 int CEPH_CAP_GCACHE ; 
 int CEPH_CAP_GEXCL ; 
 int CEPH_CAP_GLAZYIO ; 
 int CEPH_CAP_GRD ; 
 int CEPH_CAP_GSHARED ; 
 int CEPH_CAP_GWR ; 
 int CEPH_CAP_GWREXTEND ; 

__attribute__((used)) static char *gcap_string(char *s, int c)
{
	if (c & CEPH_CAP_GSHARED)
		*s++ = 's';
	if (c & CEPH_CAP_GEXCL)
		*s++ = 'x';
	if (c & CEPH_CAP_GCACHE)
		*s++ = 'c';
	if (c & CEPH_CAP_GRD)
		*s++ = 'r';
	if (c & CEPH_CAP_GWR)
		*s++ = 'w';
	if (c & CEPH_CAP_GBUFFER)
		*s++ = 'b';
	if (c & CEPH_CAP_GWREXTEND)
		*s++ = 'a';
	if (c & CEPH_CAP_GLAZYIO)
		*s++ = 'l';
	return s;
}