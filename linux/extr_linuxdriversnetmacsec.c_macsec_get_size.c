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

/* Variables and functions */
 size_t nla_total_size (int) ; 
 size_t nla_total_size_64bit (int) ; 

__attribute__((used)) static size_t macsec_get_size(const struct net_device *dev)
{
	return  nla_total_size_64bit(8) + /* IFLA_MACSEC_SCI */
		nla_total_size(1) + /* IFLA_MACSEC_ICV_LEN */
		nla_total_size_64bit(8) + /* IFLA_MACSEC_CIPHER_SUITE */
		nla_total_size(4) + /* IFLA_MACSEC_WINDOW */
		nla_total_size(1) + /* IFLA_MACSEC_ENCODING_SA */
		nla_total_size(1) + /* IFLA_MACSEC_ENCRYPT */
		nla_total_size(1) + /* IFLA_MACSEC_PROTECT */
		nla_total_size(1) + /* IFLA_MACSEC_INC_SCI */
		nla_total_size(1) + /* IFLA_MACSEC_ES */
		nla_total_size(1) + /* IFLA_MACSEC_SCB */
		nla_total_size(1) + /* IFLA_MACSEC_REPLAY_PROTECT */
		nla_total_size(1) + /* IFLA_MACSEC_VALIDATION */
		0;
}