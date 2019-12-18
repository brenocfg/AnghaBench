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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 unsigned char* MALLOC (size_t) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 scalar_t__ siphash24 (unsigned int*,int,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

char *
ssl_hello(const void *templ)
{
    unsigned char *px = (unsigned char *)templ;
    unsigned now = (unsigned)time(0);
    unsigned i;
    
    /* parse existing template to figure out size */
    size_t template_size = (px[3]<<8 | px[4]) + 5;
    
    /* allocate memory for that size and copy */
    px = MALLOC(template_size);
    memcpy(px, templ, template_size);
    
    /* set the new timestamp and randomize buffer */
    px[11] = (unsigned char)(now>>24);
    px[12] = (unsigned char)(now>>16);
    px[13] = (unsigned char)(now>> 8);
    px[14] = (unsigned char)(now>> 0);
    
    /* create a pattern to make this detectable as specfically masscan */
    for (i=4; i<32; i++) {
        static const uint64_t key[2] = {0,0};
        unsigned val = i+now;
        unsigned char c = (unsigned char)siphash24(&val, sizeof(val), key);
        
        px[11+i] = c;
    }
    
    return (char*)px;
}