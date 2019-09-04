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
struct tb_xdp_header {scalar_t__ type; } ;
struct tb_xdp_error_response {int error; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int ENOTSUPP ; 
#define  ERROR_NOT_READY 131 
#define  ERROR_NOT_SUPPORTED 130 
 scalar_t__ ERROR_RESPONSE ; 
#define  ERROR_UNKNOWN_DOMAIN 129 
#define  ERROR_UNKNOWN_PACKET 128 

__attribute__((used)) static int tb_xdp_handle_error(const struct tb_xdp_header *hdr)
{
	const struct tb_xdp_error_response *error;

	if (hdr->type != ERROR_RESPONSE)
		return 0;

	error = (const struct tb_xdp_error_response *)hdr;

	switch (error->error) {
	case ERROR_UNKNOWN_PACKET:
	case ERROR_UNKNOWN_DOMAIN:
		return -EIO;
	case ERROR_NOT_SUPPORTED:
		return -ENOTSUPP;
	case ERROR_NOT_READY:
		return -EAGAIN;
	default:
		break;
	}

	return 0;
}