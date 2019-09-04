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
typedef  int /*<<< orphan*/  buf3 ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 size_t base64_decode (char*,int,char*,size_t) ; 
 size_t base64_encode (char*,int,char*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int r_rand (unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

int
base64_selftest(void)
{
    char buf[100];
    char buf2[100];
    char buf3[100];
    size_t buf_len;
    size_t buf2_len;
    unsigned i;
    unsigned seed = (unsigned)time(0);

    buf_len = base64_encode(buf, sizeof(buf), "hello", 5);
    buf2_len = base64_decode(buf2, sizeof(buf2), buf, buf_len);
    if (buf2_len != 5 && memcmp(buf2, "hello", 5) != 0) {
        fprintf(stderr, "base64: selftest failed\n");
        return 1;
    }

    /*
     * Generate a bunch of random strings, encode them, then decode them,
     * making sure the final result matches the original string
     */
    for (i=0; i<100; i++) {
        unsigned j;
        size_t buf3_len;

        /* create a string of random bytes */
        buf_len = r_rand(&seed) % 50;
        for (j=0; j<buf_len; j++) {
            buf[j] = (char)r_rand(&seed);
        }

        /* encode it */
        buf2_len = base64_encode(buf2, sizeof(buf2), buf, buf_len);

        /* decode it back again */
        buf3_len = base64_decode(buf3, sizeof(buf3), buf2, buf2_len);

        /* now make sure result equals original */
        if (buf3_len != buf_len && memcmp(buf3, buf, buf_len) != 0) {
            fprintf(stderr, "base64: selftest failed\n");
            return 1;
        }
    }

    return 0;
}