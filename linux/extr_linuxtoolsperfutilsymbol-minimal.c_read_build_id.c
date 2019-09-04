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
typedef  int u32 ;

/* Variables and functions */
 size_t NOTE_ALIGN (int) ; 
 scalar_t__ NT_GNU_BUILD_ID ; 
 void* bswap_32 (int) ; 
 scalar_t__ memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 size_t min (size_t,size_t) ; 

__attribute__((used)) static int read_build_id(void *note_data, size_t note_len, void *bf,
			 size_t size, bool need_swap)
{
	struct {
		u32 n_namesz;
		u32 n_descsz;
		u32 n_type;
	} *nhdr;
	void *ptr;

	ptr = note_data;
	while (ptr < (note_data + note_len)) {
		const char *name;
		size_t namesz, descsz;

		nhdr = ptr;
		if (need_swap) {
			nhdr->n_namesz = bswap_32(nhdr->n_namesz);
			nhdr->n_descsz = bswap_32(nhdr->n_descsz);
			nhdr->n_type = bswap_32(nhdr->n_type);
		}

		namesz = NOTE_ALIGN(nhdr->n_namesz);
		descsz = NOTE_ALIGN(nhdr->n_descsz);

		ptr += sizeof(*nhdr);
		name = ptr;
		ptr += namesz;
		if (nhdr->n_type == NT_GNU_BUILD_ID &&
		    nhdr->n_namesz == sizeof("GNU")) {
			if (memcmp(name, "GNU", sizeof("GNU")) == 0) {
				size_t sz = min(size, descsz);
				memcpy(bf, ptr, sz);
				memset(bf + sz, 0, size - sz);
				return 0;
			}
		}
		ptr += descsz;
	}

	return -1;
}