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
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/ * STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BER_TAG_INTEGER ; 
 int /*<<< orphan*/  BER_TAG_OCTET_STRING ; 
 int /*<<< orphan*/  BER_TAG_RESULT ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  MCS_CONNECT_RESPONSE ; 
 int /*<<< orphan*/  ber_parse_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * iso_recv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcs_parse_domain_params (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_check_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_process_mcs_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RD_BOOL
mcs_recv_connect_response(STREAM mcs_data)
{
	uint8 result;
	int length;
	STREAM s;

	s = iso_recv(NULL);
	if (s == NULL)
		return False;

	ber_parse_header(s, MCS_CONNECT_RESPONSE, &length);

	ber_parse_header(s, BER_TAG_RESULT, &length);
	in_uint8(s, result);
	if (result != 0)
	{
		error("MCS connect: %d\n", result);
		return False;
	}

	ber_parse_header(s, BER_TAG_INTEGER, &length);
	in_uint8s(s, length);	/* connect id */
	mcs_parse_domain_params(s);

	ber_parse_header(s, BER_TAG_OCTET_STRING, &length);

	sec_process_mcs_data(s);
	/*
	   if (length > mcs_data->size)
	   {
	   error("MCS data length %d, expected %d\n", length,
	   mcs_data->size);
	   length = mcs_data->size;
	   }

	   in_uint8a(s, mcs_data->data, length);
	   mcs_data->p = mcs_data->data;
	   mcs_data->end = mcs_data->data + length;
	 */
	return s_check_end(s);
}