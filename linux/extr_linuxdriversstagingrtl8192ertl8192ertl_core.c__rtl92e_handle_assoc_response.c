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
struct rtllib_network {int dummy; } ;
struct rtllib_assoc_response_frame {int dummy; } ;
struct r8192_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtl92e_qos_assoc_resp (struct r8192_priv*,struct rtllib_network*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static int _rtl92e_handle_assoc_response(struct net_device *dev,
				 struct rtllib_assoc_response_frame *resp,
				 struct rtllib_network *network)
{
	struct r8192_priv *priv = rtllib_priv(dev);

	_rtl92e_qos_assoc_resp(priv, network);
	return 0;
}