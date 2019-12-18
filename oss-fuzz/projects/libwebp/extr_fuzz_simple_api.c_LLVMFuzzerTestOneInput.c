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
typedef  int uint8_t ;

/* Variables and functions */
 int FuzzHash (int const* const,size_t) ; 
 int* WebPDecodeARGB (int const* const,size_t,int*,int*) ; 
 int /*<<< orphan*/  WebPDecodeARGBInto (int const* const,size_t,int* const,size_t,int const) ; 
 int* WebPDecodeBGR (int const* const,size_t,int*,int*) ; 
 int* WebPDecodeBGRA (int const* const,size_t,int*,int*) ; 
 int /*<<< orphan*/  WebPDecodeBGRAInto (int const* const,size_t,int* const,size_t,int const) ; 
 int /*<<< orphan*/  WebPDecodeBGRInto (int const* const,size_t,int* const,size_t,int const) ; 
 int* WebPDecodeRGB (int const* const,size_t,int*,int*) ; 
 int* WebPDecodeRGBA (int const* const,size_t,int*,int*) ; 
 int /*<<< orphan*/  WebPDecodeRGBAInto (int const* const,size_t,int* const,size_t,int const) ; 
 int /*<<< orphan*/  WebPDecodeRGBInto (int const* const,size_t,int* const,size_t,int const) ; 
 int* WebPDecodeYUV (int const* const,size_t,int*,int*,int**,int**,int*,int*) ; 
 int /*<<< orphan*/  WebPDecodeYUVInto (int const* const,size_t,int* const,size_t,int,int* const,size_t,int const,int* const,size_t,int const) ; 
 int /*<<< orphan*/  WebPFree (int*) ; 
 int /*<<< orphan*/  WebPGetInfo (int const* const,size_t,int*,int*) ; 
 int /*<<< orphan*/  free (int* const) ; 
 size_t kFuzzPxLimit ; 
 scalar_t__ malloc (size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t* const data, size_t size) {
  int w, h;
  if (!WebPGetInfo(data, size, &w, &h)) return 0;
  if ((size_t)w * h > kFuzzPxLimit) return 0;

  const uint8_t value = FuzzHash(data, size);
  uint8_t* buf = NULL;

  // For *Into functions, which decode into an external buffer, an
  // intentionally too small buffer can be given with low probability.
  if (value < 0x16) {
    buf = WebPDecodeRGBA(data, size, &w, &h);
  } else if (value < 0x2b) {
    buf = WebPDecodeARGB(data, size, &w, &h);
  } else if (value < 0x40) {
    buf = WebPDecodeBGRA(data, size, &w, &h);
  } else if (value < 0x55) {
    buf = WebPDecodeRGB(data, size, &w, &h);
  } else if (value < 0x6a) {
    buf = WebPDecodeBGR(data, size, &w, &h);
  } else if (value < 0x7f) {
    uint8_t *u, *v;
    int stride, uv_stride;
    buf = WebPDecodeYUV(data, size, &w, &h, &u, &v, &stride, &uv_stride);
  } else if (value < 0xe8) {
    const int stride = (value < 0xbe ? 4 : 3) * w;
    size_t buf_size = stride * h;
    if (value % 0x10 == 0) buf_size--;
    uint8_t* const ext_buf = (uint8_t*)malloc(buf_size);
    if (value < 0x94) {
      WebPDecodeRGBAInto(data, size, ext_buf, buf_size, stride);
    } else if (value < 0xa9) {
      WebPDecodeARGBInto(data, size, ext_buf, buf_size, stride);
    } else if (value < 0xbe) {
      WebPDecodeBGRAInto(data, size, ext_buf, buf_size, stride);
    } else if (value < 0xd3) {
      WebPDecodeRGBInto(data, size, ext_buf, buf_size, stride);
    } else {
      WebPDecodeBGRInto(data, size, ext_buf, buf_size, stride);
    }
    free(ext_buf);
  } else {
    size_t luma_size = w * h;
    const int uv_stride = (w + 1) / 2;
    size_t u_size = uv_stride * (h + 1) / 2;
    size_t v_size = uv_stride * (h + 1) / 2;
    if (value % 0x10 == 0) {
      if (size & 1) luma_size--;
      if (size & 2) u_size--;
      if (size & 4) v_size--;
    }
    uint8_t* const luma_buf = (uint8_t*)malloc(luma_size);
    uint8_t* const u_buf = (uint8_t*)malloc(u_size);
    uint8_t* const v_buf = (uint8_t*)malloc(v_size);
    WebPDecodeYUVInto(data, size, luma_buf, luma_size, w /* luma_stride */,
                      u_buf, u_size, uv_stride, v_buf, v_size, uv_stride);
    free(luma_buf);
    free(u_buf);
    free(v_buf);
  }

  if (buf) WebPFree(buf);

  return 0;
}