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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 scalar_t__ E2BIG ; 
 scalar_t__ ICONV_CSNMAXLEN ; 
 int /*<<< orphan*/  efree (char*) ; 
 scalar_t__ emalloc (int) ; 
 scalar_t__ erealloc (char*,int) ; 
 scalar_t__ errno ; 
 size_t iconv (scalar_t__,char**,size_t*,char**,size_t*) ; 
 int /*<<< orphan*/  iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char* convert(const char* src, int src_len, int *new_len, const char* from_enc, const char* to_enc) {
   char* outbuf = 0;

   if(src && src_len && from_enc && to_enc) {
      size_t outlenleft = src_len;
      size_t inlenleft = src_len;
      int outlen = src_len;
      iconv_t ic;
      char* out_ptr = 0;

      if(strlen(to_enc) >= ICONV_CSNMAXLEN || strlen(from_enc) >= ICONV_CSNMAXLEN) {
         return NULL;
      }
      ic = iconv_open(to_enc, from_enc);
      if(ic != (iconv_t)-1) {
         size_t st;
         outbuf = (char*)emalloc(outlen + 1);

         out_ptr = (char*)outbuf;
         while(inlenleft) {
            st = iconv(ic, (char**)&src, &inlenleft, &out_ptr, &outlenleft);
            if(st == -1) {
               if(errno == E2BIG) {
                  int diff = out_ptr - outbuf;
                  outlen += inlenleft;
                  outlenleft += inlenleft;
                  outbuf = (char*)erealloc(outbuf, outlen + 1);
                  out_ptr = outbuf + diff;
               }
               else {
                  efree(outbuf);
                  outbuf = 0;
                  break;
               }
            }
         }
         iconv_close(ic);
      }
      outlen -= outlenleft;

      if(new_len) {
         *new_len = outbuf ? outlen : 0;
      }
      if(outbuf) {
         outbuf[outlen] = 0;
      }
   }
   return outbuf;
}