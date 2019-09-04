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

/* Variables and functions */

__attribute__((used)) static int
get_scan_code_from_ascii(int code)
{
  int rv;

  rv = 0;
  switch (code & 0xff)
  {
    case 0x30: rv = 0x0b; break; // 0
    case 0x31: rv = 0x02; break; // 1
    case 0x32: rv = 0x03; break; // 2
    case 0x33: rv = 0x04; break; // 3
    case 0x34: rv = 0x05; break; // 4
    case 0x35: rv = 0x06; break; // 5
    case 0x36: rv = 0x07; break; // 6
    case 0x37: rv = 0x08; break; // 7
    case 0x38: rv = 0x09; break; // 8
    case 0x39: rv = 0x0a; break; // 9

    case 0xbd: rv = 0x0c; break; // -
    case 0xbb: rv = 0x0d; break; // =
    case 0x08: rv = 0x0e; break; // backspace
    case 0x09: rv = 0x0f; break; // tab
    case 0xdb: rv = 0x1b; break; // ]
    case 0xdd: rv = 0x1a; break; // [
    case 0x14: rv = 0x3a; break; // capslock
    case 0xba: rv = 0x27; break; // ;
    case 0xde: rv = 0x28; break; // '
    case 0x10: rv = 0x2a; break; // shift
    case 0xbc: rv = 0x33; break; // ,
    case 0xbe: rv = 0x34; break; // .
    case 0xbf: rv = 0x35; break; // /
    case 0x0d: rv = 0x1c; break; // enter
    case 0x27: rv = 0x4d; break; // arrow right
    case 0x25: rv = 0x4b; break; // arrow left
    case 0x26: rv = 0x48; break; // arrow up
    case 0x28: rv = 0x50; break; // arrow down
    case 0x20: rv = 0x39; break; // space
    case 0xdc: rv = 0x2b; break; // backslash
    case 0xc0: rv = 0x29; break; // `
    case 0x11: rv = 0x1d; break; // ctl

    case 0x41: rv = 0x1e; break; // a
    case 0x42: rv = 0x30; break; // b
    case 0x43: rv = 0x2e; break; // c
    case 0x44: rv = 0x20; break; // d
    case 0x45: rv = 0x12; break; // e
    case 0x46: rv = 0x21; break; // f
    case 0x47: rv = 0x22; break; // g
    case 0x48: rv = 0x23; break; // h
    case 0x49: rv = 0x17; break; // i
    case 0x4a: rv = 0x24; break; // j
    case 0x4b: rv = 0x25; break; // k
    case 0x4c: rv = 0x26; break; // l
    case 0x4d: rv = 0x32; break; // m
    case 0x4e: rv = 0x31; break; // n
    case 0x4f: rv = 0x18; break; // o
    case 0x50: rv = 0x19; break; // p
    case 0x51: rv = 0x10; break; // q
    case 0x52: rv = 0x13; break; // r
    case 0x53: rv = 0x1f; break; // s
    case 0x54: rv = 0x14; break; // t
    case 0x55: rv = 0x16; break; // u
    case 0x56: rv = 0x2f; break; // v
    case 0x57: rv = 0x11; break; // w
    case 0x58: rv = 0x2d; break; // x
    case 0x59: rv = 0x15; break; // y
    case 0x5a: rv = 0x2c; break; // z
  }
  return rv;
}