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
typedef  scalar_t__ uint64_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
typedef  int /*<<< orphan*/  LZ4_stream_t ;

/* Variables and functions */
 int BILLION ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
#define  ID__LZ4_COMPRESS_DEFAULT 132 
#define  ID__LZ4_COMPRESS_FAST 131 
#define  ID__LZ4_COMPRESS_FAST_EXTSTATE 130 
#define  ID__LZ4_DECOMPRESS_FAST 129 
#define  ID__LZ4_DECOMPRESS_SAFE 128 
 int LZ4_compress_default (char const*,char*,size_t const,size_t const) ; 
 int LZ4_compress_fast (char const*,char*,size_t const,size_t const,int const) ; 
 int LZ4_compress_fast_extState (int /*<<< orphan*/ *,char const*,char*,size_t const,size_t const,int const) ; 
 int LZ4_decompress_fast (char const*,char*,size_t const) ; 
 int LZ4_decompress_safe (char const*,char*,size_t const,size_t const) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,size_t const) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  run_screaming (char*,int) ; 

uint64_t bench(
    const char *known_good_dst,
    const int function_id,
    const int iterations,
    const char *src,
    char *dst,
    const size_t src_size,
    const size_t max_dst_size,
    const size_t comp_size
  ) {
  uint64_t time_taken = 0;
  int rv = 0;
  const int warm_up = 5000;
  struct timespec start, end;
  const int acceleration = 1;
  LZ4_stream_t state;

  // Select the right function to perform the benchmark on.  We perform 5000 initial loops to warm the cache and ensure that dst
  // remains matching to known_good_dst between successive calls.
  switch(function_id) {
    case ID__LZ4_COMPRESS_DEFAULT:
      printf("Starting benchmark for function: LZ4_compress_default()\n");
      for(int junk=0; junk<warm_up; junk++)
        rv = LZ4_compress_default(src, dst, src_size, max_dst_size);
      if (rv < 1)
        run_screaming("Couldn't run LZ4_compress_default()... error code received is in exit code.", rv);
      if (memcmp(known_good_dst, dst, max_dst_size) != 0)
        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (int i=1; i<=iterations; i++)
        LZ4_compress_default(src, dst, src_size, max_dst_size);
      break;

    case ID__LZ4_COMPRESS_FAST:
      printf("Starting benchmark for function: LZ4_compress_fast()\n");
      for(int junk=0; junk<warm_up; junk++)
        rv = LZ4_compress_fast(src, dst, src_size, max_dst_size, acceleration);
      if (rv < 1)
        run_screaming("Couldn't run LZ4_compress_fast()... error code received is in exit code.", rv);
      if (memcmp(known_good_dst, dst, max_dst_size) != 0)
        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (int i=1; i<=iterations; i++)
        LZ4_compress_fast(src, dst, src_size, max_dst_size, acceleration);
      break;

    case ID__LZ4_COMPRESS_FAST_EXTSTATE:
      printf("Starting benchmark for function: LZ4_compress_fast_extState()\n");
      for(int junk=0; junk<warm_up; junk++)
        rv = LZ4_compress_fast_extState(&state, src, dst, src_size, max_dst_size, acceleration);
      if (rv < 1)
        run_screaming("Couldn't run LZ4_compress_fast_extState()... error code received is in exit code.", rv);
      if (memcmp(known_good_dst, dst, max_dst_size) != 0)
        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (int i=1; i<=iterations; i++)
        LZ4_compress_fast_extState(&state, src, dst, src_size, max_dst_size, acceleration);
      break;

//    Disabled until LZ4_compress_generic() is exposed in the header.
//    case ID__LZ4_COMPRESS_GENERIC:
//      printf("Starting benchmark for function: LZ4_compress_generic()\n");
//      LZ4_resetStream((LZ4_stream_t*)&state);
//      for(int junk=0; junk<warm_up; junk++) {
//        LZ4_resetStream((LZ4_stream_t*)&state);
//        //rv = LZ4_compress_generic_wrapper(&state, src, dst, src_size, max_dst_size, notLimited, byU16, noDict, noDictIssue, acceleration);
//        LZ4_compress_generic_wrapper(&state, src, dst, src_size, max_dst_size, acceleration);
//      }
//      if (rv < 1)
//        run_screaming("Couldn't run LZ4_compress_generic()... error code received is in exit code.", rv);
//      if (memcmp(known_good_dst, dst, max_dst_size) != 0)
//        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
//      for (int i=1; i<=iterations; i++) {
//        LZ4_resetStream((LZ4_stream_t*)&state);
//        //LZ4_compress_generic_wrapper(&state, src, dst, src_size, max_dst_size, notLimited, byU16, noDict, noDictIssue, acceleration);
//        LZ4_compress_generic_wrapper(&state, src, dst, src_size, max_dst_size, acceleration);
//      }
//      break;

    case ID__LZ4_DECOMPRESS_SAFE:
      printf("Starting benchmark for function: LZ4_decompress_safe()\n");
      for(int junk=0; junk<warm_up; junk++)
        rv = LZ4_decompress_safe(src, dst, comp_size, src_size);
      if (rv < 1)
        run_screaming("Couldn't run LZ4_decompress_safe()... error code received is in exit code.", rv);
      if (memcmp(known_good_dst, dst, src_size) != 0)
        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (int i=1; i<=iterations; i++)
        LZ4_decompress_safe(src, dst, comp_size, src_size);
      break;

    case ID__LZ4_DECOMPRESS_FAST:
      printf("Starting benchmark for function: LZ4_decompress_fast()\n");
      for(int junk=0; junk<warm_up; junk++)
        rv = LZ4_decompress_fast(src, dst, src_size);
      if (rv < 1)
        run_screaming("Couldn't run LZ4_decompress_fast()... error code received is in exit code.", rv);
      if (memcmp(known_good_dst, dst, src_size) != 0)
        run_screaming("According to memcmp(), the compressed dst we got doesn't match the known_good_dst... ruh roh.", 1);
      clock_gettime(CLOCK_MONOTONIC, &start);
      for (int i=1; i<=iterations; i++)
        LZ4_decompress_fast(src, dst, src_size);
      break;

    default:
      run_screaming("The test specified isn't valid.  Please check your code.", 1);
      break;
  }

  // Stop timer and return time taken.
  clock_gettime(CLOCK_MONOTONIC, &end);
  time_taken = BILLION *(end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

  return time_taken;
}