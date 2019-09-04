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
typedef  int /*<<< orphan*/  RBuffer ;
typedef  int /*<<< orphan*/  RBinArchOptions ;
typedef  int /*<<< orphan*/  RBin ;

/* Variables and functions */
 int I_MAGIC ; 
 int /*<<< orphan*/  r_buf_append_bytes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  r_buf_append_ut32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * r_buf_new () ; 

__attribute__((used)) static RBuffer *create(RBin *bin, const ut8 *code, int codelen, const ut8 *data, int datalen, RBinArchOptions *opt) {
	RBuffer *buf = r_buf_new ();
#define B(x, y) r_buf_append_bytes (buf, (const ut8 *) (x), y)
#define D(x) r_buf_append_ut32 (buf, x)
	D (I_MAGIC); // i386 only atm
	D (codelen);
	D (datalen);
	D (4096); // bss
	D (0); // syms
	D (8 * 4); // entry
	D (4096); // spsz
	D (4096); // pcsz
	B (code, codelen);
	if (datalen > 0) {
		B (data, datalen);
	}
	return buf;
}