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
struct buffer_st {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_add (struct buffer_st*,unsigned char) ; 
 int /*<<< orphan*/  buffer_new (struct buffer_st*) ; 
 int* dtable ; 
 scalar_t__ isspace (int) ; 

void base64_decode_xmlrpc(struct buffer_st *bfr, const char *source, int length)
{
    int i;
    int offset = 0;
    int endoffile;
    int count;

    buffer_new(bfr);

    for (i = 0; i < 255; i++) {
	dtable[i] = 0x80;
    }
    for (i = 'A'; i <= 'Z'; i++) {
        dtable[i] = 0 + (i - 'A');
    }
    for (i = 'a'; i <= 'z'; i++) {
        dtable[i] = 26 + (i - 'a');
    }
    for (i = '0'; i <= '9'; i++) {
        dtable[i] = 52 + (i - '0');
    }
    dtable['+'] = 62;
    dtable['/'] = 63;
    dtable['='] = 0;

    endoffile = 0;

    /*CONSTANTCONDITION*/
    while (1) {
	unsigned char a[4], b[4], o[3];

	for (i = 0; i < 4; i++) {
	    int c;
	    while (1) {
	      c = *(source++);
	      offset++;
	      if (offset > length) endoffile = 1;
	      if (isspace(c) || c == '\n' || c == '\r') continue;
	      break;
	    }

	    if (endoffile) {
	      /*
		if (i > 0) {
                    fprintf(stderr, "Input file incomplete.\n");
		    exit(1);
		}
	      */
		return;
	    }

	    if (dtable[(unsigned char)c] & 0x80) {
	      /*
	      fprintf(stderr, "Offset %i length %i\n", offset, length);
	      fprintf(stderr, "character '%c:%x:%c' in input file.\n", c, c, dtable[c]);
	      exit(1);
	      */
	      i--;
	      continue;
	    }
	    a[i] = (unsigned char) c;
	    b[i] = (unsigned char) dtable[c];
	}
	o[0] = (b[0] << 2) | (b[1] >> 4);
	o[1] = (b[1] << 4) | (b[2] >> 2);
	o[2] = (b[2] << 6) | b[3];
        i = a[2] == '=' ? 1 : (a[3] == '=' ? 2 : 3);
	count = 0;
	while (count < i) {
	  buffer_add(bfr, o[count++]);
	}
	if (i < 3) {
	    return;
	}
    }
}