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
typedef  int /*<<< orphan*/  ut8 ;
typedef  scalar_t__ ut64 ;
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinArchOptions ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int /*<<< orphan*/  eprintf (char*,...) ; 
 int /*<<< orphan*/  r_bin_arch_options_init (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * r_bin_create (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_bin_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_bin_new () ; 
 int /*<<< orphan*/ * r_buf_data (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  r_buf_free (int /*<<< orphan*/ *) ; 
 scalar_t__ write (int,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static int create(const char *format, const char *arch, int bits, const ut8 *code, int codelen) {
	RBin *bin = r_bin_new ();
	RBinArchOptions opts;
	RBuffer *b;
	r_bin_arch_options_init (&opts, arch, bits);
	b = r_bin_create (bin, format, code, codelen, NULL, 0, &opts);
	if (b) {
		ut64 blen;
		const ut8 *tmp = r_buf_data (b, &blen);
		if (write (1, tmp, blen) != blen) {
			eprintf ("Failed to write buffer\n");
		}
		r_buf_free (b);
	} else {
		eprintf ("Cannot create binary for this format '%s'.\n", format);
	}
	r_bin_free (bin);
	return 0;
}