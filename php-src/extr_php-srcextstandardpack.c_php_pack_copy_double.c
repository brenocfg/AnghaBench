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
typedef  int /*<<< orphan*/  uint64_t ;
struct Copy64 {double d; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,double*,int) ; 
 int /*<<< orphan*/  php_pack_reverse_int64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_pack_copy_double(int is_little_endian, void * dst, double d)
{
	union Copy64 {
		double d;
		uint64_t i;
	} m;
	m.d = d;

#ifdef WORDS_BIGENDIAN
	if (is_little_endian) {
		m.i = php_pack_reverse_int64(m.i);
	}
#else /* WORDS_BIGENDIAN */
	if (!is_little_endian) {
		m.i = php_pack_reverse_int64(m.i);
	}
#endif /* WORDS_BIGENDIAN */

	memcpy(dst, &m.d, sizeof(double));
}