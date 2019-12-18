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
struct CodaFid {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (struct CodaFid*,struct CodaFid*,int) ; 

__attribute__((used)) static inline int coda_fideq(struct CodaFid *fid1, struct CodaFid *fid2)
{
	return memcmp(fid1, fid2, sizeof(*fid1)) == 0;
}