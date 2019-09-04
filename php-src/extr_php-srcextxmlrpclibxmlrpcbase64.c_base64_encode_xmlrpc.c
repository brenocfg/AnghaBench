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
struct buffer_st {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_add (struct buffer_st*,char) ; 
 int /*<<< orphan*/  buffer_new (struct buffer_st*) ; 
 unsigned char* dtable ; 

void base64_encode_xmlrpc(struct buffer_st *b, const char *source, int length)
{
  int i, hiteof = 0;
  int offset = 0;

  buffer_new(b);

  /*	Fill dtable with character encodings.  */

  for (i = 0; i < 26; i++) {
    dtable[i] = 'A' + i;
    dtable[26 + i] = 'a' + i;
  }
  for (i = 0; i < 10; i++) {
    dtable[52 + i] = '0' + i;
  }
  dtable[62] = '+';
  dtable[63] = '/';

  while (!hiteof) {
    unsigned char igroup[3], ogroup[4];
	int c, n;

    igroup[0] = igroup[1] = igroup[2] = 0;
    for (n = 0; n < 3; n++) {
      c = *(source++);
      offset++;
      if (offset > length || offset <= 0) {
	hiteof = 1;
	break;
      }
      igroup[n] = (unsigned char) c;
    }
    if (n > 0) {
      ogroup[0] = dtable[igroup[0] >> 2];
      ogroup[1] = dtable[((igroup[0] & 3) << 4) | (igroup[1] >> 4)];
      ogroup[2] = dtable[((igroup[1] & 0xF) << 2) | (igroup[2] >> 6)];
      ogroup[3] = dtable[igroup[2] & 0x3F];

      /* Replace characters in output stream with "=" pad
	 characters if fewer than three characters were
	 read from the end of the input stream. */

      if (n < 3) {
	ogroup[3] = '=';
	if (n < 2) {
	  ogroup[2] = '=';
	}
      }
      for (i = 0; i < 4; i++) {
	buffer_add(b, ogroup[i]);
	if (!(b->offset % 72)) {
	  /* buffer_add(b, '\r'); */
	  buffer_add(b, '\n');
	}
      }
    }
  }
  /* buffer_add(b, '\r'); */
  buffer_add(b, '\n');
}