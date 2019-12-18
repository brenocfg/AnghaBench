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
typedef  void* uint64_t ;
struct Copy64 {double d; void* i; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void**,void*,int) ; 
 void* php_pack_reverse_int64 (void*) ; 

__attribute__((used)) static double php_pack_parse_double(int is_little_endian, void * src)
{
	union Copy64 {
		double d;
		uint64_t i;
	} m;
	memcpy(&m.i, src, sizeof(double));

#ifdef WORDS_BIGENDIAN
	if (is_little_endian) {
		m.i = php_pack_reverse_int64(m.i);
	}
#else /* WORDS_BIGENDIAN */
	if (!is_little_endian) {
		m.i = php_pack_reverse_int64(m.i);
	}
#endif /* WORDS_BIGENDIAN */

	return m.d;
}