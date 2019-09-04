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
struct svc_rqst {int dummy; } ;
struct svc_export {int dummy; } ;

/* Variables and functions */
 int NFSEXP_READONLY ; 
 int nfsexp_flags (struct svc_rqst*,struct svc_export*) ; 

__attribute__((used)) static int exp_rdonly(struct svc_rqst *rqstp, struct svc_export *exp)
{
	return nfsexp_flags(rqstp, exp) & NFSEXP_READONLY;
}