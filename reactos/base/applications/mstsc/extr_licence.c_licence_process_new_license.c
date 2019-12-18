#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
struct TYPE_7__ {scalar_t__ p; } ;
typedef  TYPE_1__* STREAM ;

/* Variables and functions */
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  g_licence_issued ; 
 scalar_t__ g_licence_key ; 
 int /*<<< orphan*/  in_uint16_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint32_le (TYPE_1__*,int) ; 
 int /*<<< orphan*/  in_uint8s (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rdssl_rc4_crypt (void*,char*,char*,int) ; 
 void* rdssl_rc4_info_create () ; 
 int /*<<< orphan*/  rdssl_rc4_info_delete (void*) ; 
 int /*<<< orphan*/  rdssl_rc4_set_key (void*,char*,int) ; 
 int /*<<< orphan*/  s_check_rem (TYPE_1__*,int) ; 
 int /*<<< orphan*/  save_licence (scalar_t__,int) ; 

__attribute__((used)) static void
licence_process_new_license(STREAM s)
{
	void * crypt_key;
	uint32 length;
	int i;

	in_uint8s(s, 2);	// Skip license binary blob type
	in_uint16_le(s, length);
	if (!s_check_rem(s, length))
		return;

	crypt_key = rdssl_rc4_info_create();
	rdssl_rc4_set_key(crypt_key, (char *)g_licence_key, 16);
	rdssl_rc4_crypt(crypt_key, (char *)s->p, (char *)s->p, length);
	rdssl_rc4_info_delete(crypt_key);

	/* Parse NEW_LICENSE_INFO block */
	in_uint8s(s, 4);	// skip dwVersion

	/* Skip strings, Scope, CompanyName and ProductId to get
	   to the LicenseInfo which we store in license blob. */
	length = 0;
	for (i = 0; i < 4; i++)
	{
		in_uint8s(s, length);
		in_uint32_le(s, length);
		if (!s_check_rem(s, length))
			return;
	}

	g_licence_issued = True;
	save_licence(s->p, length);
}