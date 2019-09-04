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
struct sctp_hmac {int dummy; } ;
typedef  size_t __u16 ;

/* Variables and functions */
 struct sctp_hmac* sctp_hmac_list ; 

struct sctp_hmac *sctp_auth_get_hmac(__u16 hmac_id)
{
	return &sctp_hmac_list[hmac_id];
}