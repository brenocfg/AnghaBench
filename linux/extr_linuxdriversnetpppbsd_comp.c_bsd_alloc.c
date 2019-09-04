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
struct bsd_dict {int dummy; } ;
struct bsd_db {int totlen; unsigned int hsize; unsigned int hshift; unsigned int maxmaxcode; int maxbits; int /*<<< orphan*/ * lens; void* dict; } ;

/* Variables and functions */
 scalar_t__ BSD_CURRENT_VERSION ; 
 int BSD_NBITS (unsigned char) ; 
 scalar_t__ BSD_VERSION (unsigned char) ; 
 unsigned char CI_BSD_COMPRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int MAXCODE (int) ; 
 int /*<<< orphan*/  array_size (int,unsigned int) ; 
 int /*<<< orphan*/  bsd_free (struct bsd_db*) ; 
 struct bsd_db* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* vmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *bsd_alloc (unsigned char *options, int opt_len, int decomp)
  {
    int bits;
    unsigned int hsize, hshift, maxmaxcode;
    struct bsd_db *db;

    if (opt_len != 3 || options[0] != CI_BSD_COMPRESS || options[1] != 3
	|| BSD_VERSION(options[2]) != BSD_CURRENT_VERSION)
      {
	return NULL;
      }

    bits = BSD_NBITS(options[2]);

    switch (bits)
      {
    case 9:			/* needs 82152 for both directions */
    case 10:			/* needs 84144 */
    case 11:			/* needs 88240 */
    case 12:			/* needs 96432 */
	hsize = 5003;
	hshift = 4;
	break;
    case 13:			/* needs 176784 */
	hsize = 9001;
	hshift = 5;
	break;
    case 14:			/* needs 353744 */
	hsize = 18013;
	hshift = 6;
	break;
    case 15:			/* needs 691440 */
	hsize = 35023;
	hshift = 7;
	break;
    case 16:			/* needs 1366160--far too much, */
	/* hsize = 69001; */	/* and 69001 is too big for cptr */
	/* hshift = 8; */	/* in struct bsd_db */
	/* break; */
    default:
	return NULL;
      }
/*
 * Allocate the main control structure for this instance.
 */
    maxmaxcode = MAXCODE(bits);
    db         = kzalloc(sizeof (struct bsd_db),
					    GFP_KERNEL);
    if (!db)
      {
	return NULL;
      }

/*
 * Allocate space for the dictionary. This may be more than one page in
 * length.
 */
    db->dict = vmalloc(array_size(hsize, sizeof(struct bsd_dict)));
    if (!db->dict)
      {
	bsd_free (db);
	return NULL;
      }

/*
 * If this is the compression buffer then there is no length data.
 */
    if (!decomp)
      {
	db->lens = NULL;
      }
/*
 * For decompression, the length information is needed as well.
 */
    else
      {
        db->lens = vmalloc(array_size(sizeof(db->lens[0]), (maxmaxcode + 1)));
	if (!db->lens)
	  {
	    bsd_free (db);
	    return NULL;
	  }
      }
/*
 * Initialize the data information for the compression code
 */
    db->totlen     = sizeof (struct bsd_db)   +
      		    (sizeof (struct bsd_dict) * hsize);

    db->hsize      = hsize;
    db->hshift     = hshift;
    db->maxmaxcode = maxmaxcode;
    db->maxbits    = bits;

    return (void *) db;
  }