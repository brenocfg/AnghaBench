#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct timespec64 {int dummy; } ;
struct ntlmssp2_name {int /*<<< orphan*/  length; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int len; unsigned char* response; } ;
struct cifs_ses {TYPE_1__ auth_key; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 unsigned int NTLMSSP_AV_EOL ; 
 unsigned int NTLMSSP_AV_TIMESTAMP ; 
 int /*<<< orphan*/  cifs_UnixTimeToNT (struct timespec64) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __le64
find_timestamp(struct cifs_ses *ses)
{
	unsigned int attrsize;
	unsigned int type;
	unsigned int onesize = sizeof(struct ntlmssp2_name);
	unsigned char *blobptr;
	unsigned char *blobend;
	struct ntlmssp2_name *attrptr;
	struct timespec64 ts;

	if (!ses->auth_key.len || !ses->auth_key.response)
		return 0;

	blobptr = ses->auth_key.response;
	blobend = blobptr + ses->auth_key.len;

	while (blobptr + onesize < blobend) {
		attrptr = (struct ntlmssp2_name *) blobptr;
		type = le16_to_cpu(attrptr->type);
		if (type == NTLMSSP_AV_EOL)
			break;
		blobptr += 2; /* advance attr type */
		attrsize = le16_to_cpu(attrptr->length);
		blobptr += 2; /* advance attr size */
		if (blobptr + attrsize > blobend)
			break;
		if (type == NTLMSSP_AV_TIMESTAMP) {
			if (attrsize == sizeof(u64))
				return *((__le64 *)blobptr);
		}
		blobptr += attrsize; /* advance attr value */
	}

	ktime_get_real_ts64(&ts);
	return cpu_to_le64(cifs_UnixTimeToNT(ts));
}