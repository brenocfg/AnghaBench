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
typedef  int ut32 ;
typedef  int st32 ;

/* Variables and functions */

st32 get_hashfunc_02(st32 arg1, st32 arg2) {
	char v4 = 0;
	st32 v2 = arg2 & 0xFE000000;
	if ( (arg2 & 0xFE000000u) > 0x72000000 ) {
		if ( (ut32)v2 <= 0xD8000000 ) {
			if ( v2 != 0xd8000000) {
				if ( (ut32)v2 > 0xC4000000 ) {
					if ( (ut32)v2 > 0xCE000000 ) {
						if ( (ut32)v2 > 0xD4000000 ) {
							if (v2 == -704643072) {
								return 95;
							}
							return arg1;
						}
						if ( v2 != -738197504 && v2 != -805306368 ) {
							if (v2 == -771751936) {
								return 95;
							}
							return arg1;
						}
					} else {
						if ( v2 != -838860800 ) {
							if ( (ut32)v2 > 0xCA000000 ) {
								if (v2 == -872415232) {
									return 95;
								}
								return arg1;
							}
							if ( v2 != -905969664 && v2 != -973078528 ) {
								if (v2 == -939524096) {
									return 95;
								}
								return arg1;
							}
						}
					}
				} else {
					if ( v2 != -1006632960 ) {
						if ( (ut32)v2 <= 0x7E000000 ) {
							if ( v2 != 2113929216 ) {
								if ( (ut32)v2 > 0x78000000 ) {
									if (v2 != 2046820352 && v2 != 2080374784) {
										return arg1;
									}
								} else {
									if ( v2 != 2013265920 && v2 != 1946157056 ) {
										if (v2 == 1979711488) {
											return 226;
										}
										return arg1;
									}
								}
							}
							return 226;
						}
						if ( (ut32)v2 > 0xC0000000 ) {
							if (v2 == -1040187392) {
								return 95;
							}
							return arg1;
						}
						if ( v2 != 0xC0000000 ) {
							if (v2 == -1610612736) {
								return 540;
							}
							if (v2 == -1577058304) {
								return 541;
							}
							return arg1;
						}
					}
				}
			}
			return 95;
		}
		if ( (ut32)v2 > 0xEC000000 ) {
			if ( (ut32)v2 > 0xF6000000 ) {
				if ( (ut32)v2 > 0xFC000000 ) {
					if (v2 != -33554432) {
						return arg1;
					}
					return 96;
				}
				if (v2 == -67108864 || v2 == -134217728) {
					return 96;
				}
				v4 = v2 == -100663296;
			} else {
				if (v2 == -167772160) {
					return 96;
				}
				if ( (ut32)v2 > 0xF2000000 ) {
					v4 = v2 == -201326592;
				} else {
					if (v2 == -234881024 || v2 == -301989888) {
						return 96;
					}
					v4 = v2 == -268435456;
				}
			}
		} else {
			if (v2 == -335544320) {
				return 96;
			}
			if ( (ut32)v2 > 0xE2000000 ) {
				if ( (ut32)v2 > 0xE8000000 ) {
					v4 = v2 == -369098752;
				} else {
					if (v2 == -402653184 || v2 == -469762048) {
						return 96;
					}
					v4 = v2 == -436207616;
				}
			} else {
				if (v2 == -503316480) {
					return 96;
				}
				if ( (ut32)v2 <= 0xDE000000 ) {
					if (v2 != -570425344 && v2 != -637534208 && v2 != -603979776) {
						return arg1;
					}
					return 95;
				}
				v4 = v2 == -536870912;
			}
		}
		if (!v4) {
			return arg1;
		}
		return 96;
	}
	if ((arg2 & 0xFE000000) == 1912602624) {
		return 226;
	}
	if ( (ut32)v2 > 0x48000000 ) {
		if ( (ut32)v2 <= 0x5E000000 ) {
			if ( v2 != 1577058304 ) {
				if ( (ut32)v2 > 0x54000000 ) {
					if ( (ut32)v2 > 0x5A000000 ) {
						if (v2 != 1543503872) {
							return arg1;
						}
					} else {
						if ( v2 != 1509949440 && v2 != 1442840576 ) {
							if (v2 == 1476395008) {
								return 178;
							}
							return arg1;
						}
					}
				} else {
					if ( v2 != 1409286144 ) {
						if ( (ut32)v2 > 0x4E000000 ) {
							if ( v2 != 1342177280 ) {
								if (v2 == 1375731712) {
									return 178;
								}
								return arg1;
							}
						} else {
							if ( v2 != 1308622848 && v2 != 1241513984 ) {
								if (v2 == 1275068416) {
									return 178;
								}
								return arg1;
							}
						}
					}
				}
			}
			return 178;
		}
		if ( (ut32)v2 > 0x68000000 ) {
			if ( (ut32)v2 > 0x6E000000 ) {
				if (v2 == 1879048192) {
					return 226;
				}
				return arg1;
			}
			if ( v2 != 1845493760 && v2 != 1778384896 ) {
				if (v2 == 1811939328) {
					return 226;
				}
				return arg1;
			}
		} else {
			if ( v2 != 1744830464 ) {
				if ( (ut32)v2 > 0x64000000 ) {
					if (v2 == 1711276032) {
						return 226;
					}
					return arg1;
				}
				if ( v2 != 1677721600 && v2 != 1610612736 ) {
					if (v2 == 1644167168) {
						return 226;
					}
					return arg1;
				}
			}
		}
		return 226;
	}
	if (v2 == 1207959552) {
		return 178;
	}
	if ( (ut32)v2 <= 0x14000000 ) {
		if ( v2 != 335544320 ) {
			if ( (ut32)v2 > 0xA000000 ) {
				if ( (ut32)v2 > 0x10000000 ) {
					if (v2 == 301989888) {
						return 142;
					}
					return arg1;
				}
				if ( v2 != 268435456 && v2 != 201326592 ) {
					if (v2 == 234881024) {
						return 142;
					}
					return arg1;
				}
			} else {
				if ( v2 != 167772160 ) {
					if ( (ut32)v2 > 0x4000000 ) {
						if ( v2 != 100663296 ) {
							if (v2 == 134217728) {
								return 142;
							}
							return arg1;
						}
					} else {
						if ( v2 != 67108864 && v2 ) {
							if (v2 == 33554432) {
								return 142;
							}
							return arg1;
						}
					}
				}
			}
		}
		return 142;
	}
	if ( (ut32)v2 > 0x1E000000 ) {
		if ( (ut32)v2 > 0x44000000 ) {
			if (v2 == 1174405120) {
				return 178;
			}
			return arg1;
		}
		if ( v2 != 1140850688 && v2 != 0x40000000 ) {
			if (v2 == 1107296256) {
				return 178;
			}
			return arg1;
		}
		return 178;
	}
	if (v2 == 503316480) {
		return 142;
	}
	if ( (ut32)v2 <= 0x1A000000 ) {
		if ( v2 != 436207616 && v2 != 369098752 ) {
			if (v2 == 402653184) {
				return 142;
			}
			return arg1;
		}
		return 142;
	}
	if (v2 == 469762048) {
		return 142;
	}
	return arg1;
}