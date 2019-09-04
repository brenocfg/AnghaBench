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
struct x25_facilities {char pacsize_in; char pacsize_out; char winsize_in; char winsize_out; int /*<<< orphan*/  throughput; int /*<<< orphan*/  reverse; } ;
struct x25_dte_facilities {int calling_len; int called_len; int /*<<< orphan*/  called_ae; int /*<<< orphan*/  calling_ae; } ;

/* Variables and functions */
 int /*<<< orphan*/  X25_DTE_SERVICES ; 
 int /*<<< orphan*/  X25_FAC_CALLED_AE ; 
 int /*<<< orphan*/  X25_FAC_CALLING_AE ; 
 int /*<<< orphan*/  X25_FAC_PACKET_SIZE ; 
 int /*<<< orphan*/  X25_FAC_REVERSE ; 
 int /*<<< orphan*/  X25_FAC_THROUGHPUT ; 
 int /*<<< orphan*/  X25_FAC_WINDOW_SIZE ; 
 int /*<<< orphan*/  X25_MARKER ; 
 unsigned long X25_MASK_CALLED_AE ; 
 unsigned long X25_MASK_CALLING_AE ; 
 unsigned long X25_MASK_PACKET_SIZE ; 
 unsigned long X25_MASK_REVERSE ; 
 unsigned long X25_MASK_THROUGHPUT ; 
 unsigned long X25_MASK_WINDOW_SIZE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

int x25_create_facilities(unsigned char *buffer,
		struct x25_facilities *facilities,
		struct x25_dte_facilities *dte_facs, unsigned long facil_mask)
{
	unsigned char *p = buffer + 1;
	int len;

	if (!facil_mask) {
		/*
		 * Length of the facilities field in call_req or
		 * call_accept packets
		 */
		buffer[0] = 0;
		len = 1; /* 1 byte for the length field */
		return len;
	}

	if (facilities->reverse && (facil_mask & X25_MASK_REVERSE)) {
		*p++ = X25_FAC_REVERSE;
		*p++ = facilities->reverse;
	}

	if (facilities->throughput && (facil_mask & X25_MASK_THROUGHPUT)) {
		*p++ = X25_FAC_THROUGHPUT;
		*p++ = facilities->throughput;
	}

	if ((facilities->pacsize_in || facilities->pacsize_out) &&
	    (facil_mask & X25_MASK_PACKET_SIZE)) {
		*p++ = X25_FAC_PACKET_SIZE;
		*p++ = facilities->pacsize_in ? : facilities->pacsize_out;
		*p++ = facilities->pacsize_out ? : facilities->pacsize_in;
	}

	if ((facilities->winsize_in || facilities->winsize_out) &&
	    (facil_mask & X25_MASK_WINDOW_SIZE)) {
		*p++ = X25_FAC_WINDOW_SIZE;
		*p++ = facilities->winsize_in ? : facilities->winsize_out;
		*p++ = facilities->winsize_out ? : facilities->winsize_in;
	}

	if (facil_mask & (X25_MASK_CALLING_AE|X25_MASK_CALLED_AE)) {
		*p++ = X25_MARKER;
		*p++ = X25_DTE_SERVICES;
	}

	if (dte_facs->calling_len && (facil_mask & X25_MASK_CALLING_AE)) {
		unsigned int bytecount = (dte_facs->calling_len + 1) >> 1;
		*p++ = X25_FAC_CALLING_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->calling_len;
		memcpy(p, dte_facs->calling_ae, bytecount);
		p += bytecount;
	}

	if (dte_facs->called_len && (facil_mask & X25_MASK_CALLED_AE)) {
		unsigned int bytecount = (dte_facs->called_len % 2) ?
		dte_facs->called_len / 2 + 1 :
		dte_facs->called_len / 2;
		*p++ = X25_FAC_CALLED_AE;
		*p++ = 1 + bytecount;
		*p++ = dte_facs->called_len;
		memcpy(p, dte_facs->called_ae, bytecount);
		p+=bytecount;
	}

	len       = p - buffer;
	buffer[0] = len - 1;

	return len;
}