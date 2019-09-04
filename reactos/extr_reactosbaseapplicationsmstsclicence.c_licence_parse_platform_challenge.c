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
typedef  int /*<<< orphan*/  uint8 ;
typedef  scalar_t__ uint16 ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  int /*<<< orphan*/  RD_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 scalar_t__ LICENCE_SIGNATURE_SIZE ; 
 scalar_t__ LICENCE_TOKEN_SIZE ; 
 int /*<<< orphan*/  error (char*,scalar_t__) ; 
 int /*<<< orphan*/  in_uint16_le (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  in_uint8s (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_check_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RD_BOOL
licence_parse_platform_challenge(STREAM s, uint8 ** token, uint8 ** signature)
{
	uint16 tokenlen;

	in_uint8s(s, 6);	/* unknown: f8 3d 15 00 04 f6 */

	in_uint16_le(s, tokenlen);
	if (tokenlen != LICENCE_TOKEN_SIZE)
	{
		error("token len %d\n", tokenlen);
		return False;
	}

	in_uint8p(s, *token, tokenlen);
	in_uint8p(s, *signature, LICENCE_SIGNATURE_SIZE);

	return s_check_end(s);
}