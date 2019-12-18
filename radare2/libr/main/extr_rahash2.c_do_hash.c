#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut64 ;
struct TYPE_9__ {int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {int len; int /*<<< orphan*/ * buf; scalar_t__ prefix; } ;
struct TYPE_7__ {int /*<<< orphan*/  desc; } ;
typedef  TYPE_1__ RIO ;
typedef  int /*<<< orphan*/  RHash ;

/* Variables and functions */
 int R_HASH_ALL ; 
 int R_HASH_NONE ; 
 TYPE_4__* _s ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  compare_hashes (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int*) ; 
 int /*<<< orphan*/  do_hash_internal (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  do_hash_print (int /*<<< orphan*/ *,int,int,char,int) ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 long long from ; 
 scalar_t__ incremental ; 
 scalar_t__ iterations ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int quiet ; 
 int /*<<< orphan*/  r_hash_do_begin (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_hash_do_end (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  r_hash_do_spice (int /*<<< orphan*/ *,int,scalar_t__,TYPE_4__*) ; 
 int /*<<< orphan*/  r_hash_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_hash_name (int) ; 
 int r_hash_name_to_bits (char const*) ; 
 int /*<<< orphan*/ * r_hash_new (int,int) ; 
 int r_hash_size (int) ; 
 int r_io_desc_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_pread_at (TYPE_1__*,int,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ s ; 
 long long to ; 

__attribute__((used)) static int do_hash(const char *file, const char *algo, RIO *io, int bsize, int rad, int ule, const ut8 *compare) {
	ut64 j, fsize, algobit = r_hash_name_to_bits (algo);
	RHash *ctx;
	ut8 *buf;
	int ret = 0;
	ut64 i;
	bool first = true;
	if (algobit == R_HASH_NONE) {
		eprintf ("rahash2: Invalid hashing algorithm specified\n");
		return 1;
	}
	fsize = r_io_desc_size (io->desc);
	if (fsize < 1) {
		eprintf ("rahash2: Invalid file size\n");
		return 1;
	}
	if (bsize < 0) {
		bsize = fsize / -bsize;
	}
	if (bsize == 0 || bsize > fsize) {
		bsize = fsize;
	}
	if (to == 0LL) {
		to = fsize;
	}
	if (from > to) {
		eprintf ("rahash2: Invalid -f -t range\n");
		return 1;
	}
	if (fsize == -1LL) {
		eprintf ("rahash2: Unknown file size\n");
		return 1;
	}
	buf = calloc (1, bsize + 1);
	if (!buf) {
		return 1;
	}
	ctx = r_hash_new (true, algobit);

	if (rad == 'j') {
		printf ("[");
	}
	if (incremental) {
		for (i = 1; i < R_HASH_ALL; i <<= 1) {
			if (algobit & i) {
				ut64 hashbit = i & algobit;
				int dlen = r_hash_size (hashbit);
				r_hash_do_begin (ctx, i);
				if (s.buf && s.prefix) {
					do_hash_internal (ctx, hashbit, s.buf, s.len, rad, 0, ule);
				}
				for (j = from; j < to; j += bsize) {
					int len = ((j + bsize) > to)? (to - j): bsize;
					r_io_pread_at (io, j, buf, len);
					do_hash_internal (ctx, hashbit, buf, len, rad, 0, ule);
				}
				if (s.buf && !s.prefix) {
					do_hash_internal (ctx, hashbit, s.buf, s.len, rad, 0, ule);
				}
				r_hash_do_end (ctx, i);
				if (iterations > 0) {
					r_hash_do_spice (ctx, i, iterations, _s);
				}
				if (!*r_hash_name (i)) {
					continue;
				}
				if (rad == 'j') {
					if (first) {
						first = false;
					} else {
						printf (",");
					}
				}
				if (!quiet && rad != 'j') {
					printf ("%s: ", file);
				}
				do_hash_print (ctx, i, dlen, quiet? 'n': rad, ule);
				if (quiet == 1) {
					printf (" %s\n", file);
				} else {
					if (quiet && !rad) {
						printf ("\n");
					}
				}
			}
		}
		if (_s) {
			free (_s->buf);
		}
	} else {
		/* iterate over all algorithm bits */
		if (s.buf) {
			eprintf ("Warning: Seed ignored on per-block hashing.\n");
		}
		for (i = 1; i < R_HASH_ALL; i <<= 1) {
			ut64 f, t, ofrom, oto;
			if (algobit & i) {
				ut64 hashbit = i & algobit;
				ofrom = from;
				oto = to;
				f = from;
				t = to;
				for (j = f; j < t; j += bsize) {
					int nsize = (j + bsize < fsize)? bsize: (fsize - j);
					r_io_pread_at (io, j, buf, bsize);
					from = j;
					to = j + bsize;
					if (to > fsize) {
						to = fsize;
					}
					do_hash_internal (ctx, hashbit, buf, nsize, rad, 1, ule);
				}
				do_hash_internal (ctx, hashbit, NULL, 0, rad, 1, ule);
				from = ofrom;
				to = oto;
			}
		}
	}
	if (rad == 'j') {
		printf ("]\n");
	}

	compare_hashes (ctx, compare, r_hash_size (algobit), &ret);
	r_hash_free (ctx);
	free (buf);
	return ret;
}