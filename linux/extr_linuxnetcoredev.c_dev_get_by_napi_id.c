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
struct net_device {int dummy; } ;
struct napi_struct {struct net_device* dev; } ;

/* Variables and functions */
 unsigned int MIN_NAPI_ID ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct napi_struct* napi_by_id (unsigned int) ; 
 int /*<<< orphan*/  rcu_read_lock_held () ; 

struct net_device *dev_get_by_napi_id(unsigned int napi_id)
{
	struct napi_struct *napi;

	WARN_ON_ONCE(!rcu_read_lock_held());

	if (napi_id < MIN_NAPI_ID)
		return NULL;

	napi = napi_by_id(napi_id);

	return napi ? napi->dev : NULL;
}