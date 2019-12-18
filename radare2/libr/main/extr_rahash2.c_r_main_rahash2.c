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
typedef  char ut8 ;
typedef  int ut64 ;
typedef  scalar_t__ st64 ;
struct TYPE_2__ {int len; char* buf; scalar_t__ prefix; } ;
typedef  int /*<<< orphan*/  RIODesc ;
typedef  int /*<<< orphan*/  RIO ;
typedef  int /*<<< orphan*/  RHash ;

/* Variables and functions */
 int INSIZE ; 
 int R_HASH_ALL ; 
 int /*<<< orphan*/  R_PERM_R ; 
 scalar_t__ _s ; 
 int /*<<< orphan*/  algolist () ; 
 int /*<<< orphan*/  atoi (void*) ; 
 int /*<<< orphan*/  compare_hashes (int /*<<< orphan*/ *,char*,int,int*) ; 
 int do_hash (char*,char const*,int /*<<< orphan*/ *,int,int,int,char*) ; 
 int /*<<< orphan*/  do_hash_internal (int /*<<< orphan*/ *,int,char const*,int,int,int,int) ; 
 int /*<<< orphan*/  do_hash_seed (char const*) ; 
 int do_help (int) ; 
 int encrypt_or_decrypt (char const*,int,char*,int,char*,int,int /*<<< orphan*/ ) ; 
 int encrypt_or_decrypt_file (char const*,int,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintf (char*,...) ; 
 size_t fread (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int from ; 
 int incremental ; 
 int /*<<< orphan*/  is_power_of_two (int) ; 
 int /*<<< orphan*/  iterations ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  quiet ; 
 scalar_t__ r_file_is_directory (char*) ; 
 int r_getopt (int,char**,char*) ; 
 int /*<<< orphan*/  r_hash_free (int /*<<< orphan*/ *) ; 
 int r_hash_name_to_bits (char const*) ; 
 int /*<<< orphan*/ * r_hash_new (int,int) ; 
 int r_hash_size (int) ; 
 int r_hex_str2bin (char const*,char*) ; 
 int /*<<< orphan*/  r_io_desc_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_io_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * r_io_new () ; 
 int /*<<< orphan*/ * r_io_open_nomap (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_io_pwrite_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int r_main_version_print (char*) ; 
 int r_num_math (int /*<<< orphan*/ *,void*) ; 
 void* r_optarg ; 
 int r_optind ; 
 scalar_t__ r_stdin_slurp (int*) ; 
 char* r_str_newf (char*,int) ; 
 int r_str_unescape (char*) ; 
 int /*<<< orphan*/  r_sys_cmdf (char*,char const*,char*) ; 
 TYPE_1__ s ; 
 int /*<<< orphan*/  setHashString (void*,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int to ; 

int r_main_rahash2(int argc, char **argv) {
	ut64 i;
	int ret, c, rad = 0, bsize = 0, numblocks = 0, ule = 0;
	const char *algo = "sha256"; /* default hashing algorithm */
	const char *seed = NULL;
	const char *decrypt = NULL;
	const char *encrypt = NULL;
	char *hashstr = NULL;
	ut8 *iv = NULL;
	int ivlen = -1;
	char *ivseed = NULL;
	const char *compareStr = NULL;
	const char *ptype = NULL;
	ut8 *compareBin = NULL;
	int hashstr_len = -1;
	int hashstr_hex = 0;
	size_t bytes_read = 0;// bytes read from stdin
	ut64 algobit;
	RHash *ctx;
	RIO *io;

	while ((c = r_getopt (argc, argv, "p:jD:rveE:a:i:I:S:s:x:b:nBhf:t:kLqc:")) != -1) {
		switch (c) {
		case 'q': quiet++; break;
		case 'i':
			iterations = atoi (r_optarg);
			if (iterations < 0) {
				eprintf ("error: -i argument must be positive\n");
				return 1;
			}
			break;
		case 'j': rad = 'j'; break;
		case 'S': seed = r_optarg; break;
		case 'I': ivseed = r_optarg; break;
		case 'n': numblocks = 1; break;
		case 'D': decrypt = r_optarg; break;
		case 'E': encrypt = r_optarg; break;
		case 'L': algolist (); return 0;
		case 'e': ule = 1; break;
		case 'r': rad = 1; break;
		case 'k': rad = 2; break;
		case 'p': ptype = r_optarg; break;
		case 'a': algo = r_optarg; break;
		case 'B': incremental = false; break;
		case 'b': bsize = (int) r_num_math (NULL, r_optarg); break;
		case 'f': from = r_num_math (NULL, r_optarg); break;
		case 't': to = 1 + r_num_math (NULL, r_optarg); break;
		case 'v': return r_main_version_print ("rahash2");
		case 'h': return do_help (0);
		case 's': setHashString (r_optarg, 0); break;
		case 'x': setHashString (r_optarg, 1); break;
		case 'c': compareStr = r_optarg; break;
		default: return do_help (0);
		}
	}
	if (encrypt && decrypt) {
		eprintf ("rahash2: Option -E and -D are incompatible with each other.\n");
		return 1;
	}
	if (compareStr) {
		int compareBin_len;
		if (bsize && !incremental) {
			eprintf ("rahash2: Option -c incompatible with -b and -B options.\n");
			return 1;
		}
		bool flag = false;
		if (encrypt) {
			flag = !strcmp (encrypt, "base64") || !strcmp (encrypt, "base91");
		} else if (decrypt) {
			flag = !strcmp (decrypt, "base64") || !strcmp (decrypt, "base91");
		}
		if (flag) {
			eprintf ("rahash2: Option -c incompatible with -E base64, -E base91, -D base64 or -D base91 options.\n");
			return 1;
		}
		algobit = r_hash_name_to_bits (algo);
		// if algobit represents a single algorithm then it's a power of 2
		if (!is_power_of_two (algobit)) {
			eprintf ("rahash2: Option -c incompatible with multiple algorithms in -a.\n");
			return 1;
		}
		compareBin = malloc ((strlen (compareStr) + 1) * 2);
		if (!compareBin) {
			return 1;
		}
		compareBin_len = r_hex_str2bin (compareStr, compareBin);
		if (compareBin_len < 1) {
			eprintf ("rahash2: Invalid -c hex hash\n");
			free (compareBin);
			return 1;
		} else if (compareBin_len != r_hash_size (algobit))   {
			eprintf (
				"rahash2: Given -c hash has %d byte(s) but the selected algorithm returns %d byte(s).\n",
				compareBin_len,
				r_hash_size (algobit));
			free (compareBin);
			return 1;
		}
	}
	if ((st64) from >= 0 && (st64) to < 0) {
		to = 0; // end of file
	}
	if (from || to) {
		if (to && from >= to) {
			eprintf ("Invalid -f or -t offsets\n");
			return 1;
		}
	}
	if (ptype) {
		// TODO: support p=%s (horizontal bars)
		// TODO: list supported statistical metrics
		// TODO: support -f and -t
		for (i = r_optind; i < argc; i++) {
			printf ("%s:\n", argv[i]);
			r_sys_cmdf ("r2 -qfnc \"p==%s 100\" \"%s\"", ptype, argv[i]);
		}
		return 0;
	}
	// convert iv to hex or string.
	if (ivseed) {
		iv = (ut8 *) malloc (strlen (ivseed) + 128);
		if (!strncmp (ivseed, "s:", 2)) {
			strcpy ((char *) iv, ivseed + 2);
			ivlen = strlen (ivseed + 2);
		} else {
			ivlen = r_hex_str2bin (ivseed, iv);
			if (ivlen < 1) {
				strcpy ((char *) iv, ivseed);
				ivlen = strlen (ivseed);
			}
		}
	}
	do_hash_seed (seed);
	if (hashstr) {
#define INSIZE 32768
		ret = 0;
		if (!strcmp (hashstr, "-")) {
			hashstr = malloc (INSIZE);
			if (!hashstr) {
				free (iv);
				return 1;
			}
			bytes_read = fread ((void *) hashstr, 1, INSIZE - 1, stdin);
			if (bytes_read < 1) {
				bytes_read = 0;
			}
			hashstr[bytes_read] = '\0';
			hashstr_len = bytes_read;
		}
		if (hashstr_hex) {
			ut8 *out = malloc ((strlen (hashstr) + 1) * 2);
			hashstr_len = r_hex_str2bin (hashstr, out);
			if (hashstr_len < 1) {
				eprintf ("Invalid hex string\n");
				free (out);
				free (iv);
				return 1;
			}
			hashstr = (char *) out;
			/* out memleaks here, hashstr can't be freed */
		} else {
			if (!bytes_read) {
				hashstr_len = strlen (hashstr);
			}
		}
		if (from) {
			if (from >= hashstr_len) {
				eprintf ("Invalid -f.\n");
				free (iv);
				return 1;
			}
		}
		if (to) {
			if (to > hashstr_len) {
				eprintf ("Invalid -t.\n");
				return 1;
			}
		} else {
			to = hashstr_len;
		}
		hashstr = hashstr + from;
		hashstr_len = to - from;
		hashstr[hashstr_len] = '\0';
		if (!bytes_read && !hashstr_hex) {
			hashstr_len = r_str_unescape (hashstr);
		}
		if (encrypt) {
			return encrypt_or_decrypt (encrypt, 0, hashstr, hashstr_len, iv, ivlen, 0);
		} else if (decrypt) {
			return encrypt_or_decrypt (decrypt, 1, hashstr, hashstr_len, iv, ivlen, 0);
		} else {
			char *str = (char *) hashstr;
			int strsz = hashstr_len;
			if (_s) {
				// alloc/concat/resize
				str = malloc (strsz + s.len);
				if (s.prefix) {
					memcpy (str, s.buf, s.len);
					memcpy (str + s.len, hashstr, hashstr_len);
				} else {
					memcpy (str, hashstr, hashstr_len);
					memcpy (str + strsz, s.buf, s.len);
				}
				strsz += s.len;
				str[strsz] = 0;
			}
			algobit = r_hash_name_to_bits (algo);
			if (algobit == 0) {
				eprintf ("Invalid algorithm. See -E, -D maybe?\n");
				if (str != hashstr) {
					free (str);
				}
				free (iv);
				return 1;
			}
			for (i = 1; i < R_HASH_ALL; i <<= 1) {
				if (algobit & i) {
					ut64 hashbit = i & algobit;
					ctx = r_hash_new (true, hashbit);
					from = 0;
					to = strsz;
					do_hash_internal (ctx, hashbit, (const ut8 *) str, strsz, rad, 1, ule);
					compare_hashes (ctx, compareBin, r_hash_size (algobit), &ret);
					r_hash_free (ctx);
				}
			}
			if (_s) {
				if (str != hashstr) {
					free (str);
				}
				free (s.buf);
			}
			return ret;
		}
	}
	if (r_optind >= argc) {
		free (iv);
		return do_help (1);
	}
	if (numblocks) {
		bsize = -bsize;
	} else if (bsize < 0) {
		eprintf ("rahash2: Invalid block size\n");
		free (iv);
		return 1;
	}

	io = r_io_new ();
	for (ret = 0, i = r_optind; i < argc; i++) {
		if (encrypt) {// for encrytion when files are provided
			int rt = encrypt_or_decrypt_file (encrypt, 0, argv[i], iv, ivlen, 0);
			if (rt == -1) {
				continue;
			} else {
				return rt;
			}
		} else if (decrypt) {
			int rt = encrypt_or_decrypt_file (decrypt, 1, argv[i], iv, ivlen, 0);
			if (rt == -1) {
				continue;
			} else {
				return rt;
			}
		} else {
			RIODesc *desc = NULL;
			if (!strcmp (argv[i], "-")) {
				int sz = 0;
				ut8 *buf = (ut8 *) r_stdin_slurp (&sz);
				char *uri = r_str_newf ("malloc://%d", sz);
				if (sz > 0) {
					desc = r_io_open_nomap (io, uri, R_PERM_R, 0);
					if (!desc) {
						eprintf ("rahash2: Cannot open malloc://1024\n");
						free (iv);
						return 1;
					}
					r_io_pwrite_at (io, 0, buf, sz);
				}
				free (uri);
			} else {
				if (r_file_is_directory (argv[i])) {
					eprintf ("rahash2: Cannot hash directories\n");
					free (iv);
					return 1;
				}
				desc = r_io_open_nomap (io, argv[i], R_PERM_R, 0);
				if (!desc) {
					eprintf ("rahash2: Cannot open '%s'\n", argv[i]);
					free (iv);
					return 1;
				}
			}
			ret |= do_hash (argv[i], algo, io, bsize, rad, ule, compareBin);
			to = 0;
			r_io_desc_close (desc);
		}
	}
	free (hashstr);
	r_io_free (io);
	free (iv);

	return ret;
}