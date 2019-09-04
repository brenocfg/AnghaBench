#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int instruction; TYPE_2__* ops; } ;
struct TYPE_9__ {int jump; int addr; int fail; int size; void* type; } ;
struct TYPE_7__ {int imm; } ;
struct TYPE_8__ {TYPE_1__ op; } ;
typedef  TYPE_3__ RAnalOp ;
typedef  TYPE_4__ HexInsn ;

/* Variables and functions */
#define  HEX_INS_CALL__R22_2 432 
#define  HEX_INS_DEALLOC_RETURN 431 
#define  HEX_INS_DUPLEX_IF__P0_NEW__RD____0___DEALLOC_RETURN 430 
#define  HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT 429 
#define  HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF__P0__DEALLOC_RETURN 428 
#define  HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 427 
#define  HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF___NOT__P0__DEALLOC_RETURN 426 
#define  HEX_INS_DUPLEX_IF__P0__RD____0___DEALLOC_RETURN 425 
#define  HEX_INS_DUPLEX_IF__P0__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT 424 
#define  HEX_INS_DUPLEX_IF__P0__RD____0___IF__P0__DEALLOC_RETURN 423 
#define  HEX_INS_DUPLEX_IF__P0__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 422 
#define  HEX_INS_DUPLEX_IF__P0__RD____0___IF___NOT__P0__DEALLOC_RETURN 421 
#define  HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___DEALLOC_RETURN 420 
#define  HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT 419 
#define  HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF__P0__DEALLOC_RETURN 418 
#define  HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 417 
#define  HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF___NOT__P0__DEALLOC_RETURN 416 
#define  HEX_INS_DUPLEX_IF___NOT__P0__RD____0___DEALLOC_RETURN 415 
#define  HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT 414 
#define  HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF__P0__DEALLOC_RETURN 413 
#define  HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 412 
#define  HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF___NOT__P0__DEALLOC_RETURN 411 
#define  HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____DEALLOC_RETURN 410 
#define  HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF__P0_NEW__DEALLOC_RETURN_NT 409 
#define  HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF__P0__DEALLOC_RETURN 408 
#define  HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 407 
#define  HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF___NOT__P0__DEALLOC_RETURN 406 
#define  HEX_INS_DUPLEX_RDD___COMBINE__RS___0____DEALLOC_RETURN 405 
#define  HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF__P0_NEW__DEALLOC_RETURN_NT 404 
#define  HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF__P0__DEALLOC_RETURN 403 
#define  HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 402 
#define  HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF___NOT__P0__DEALLOC_RETURN 401 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0__RS____DEALLOC_RETURN 400 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF__P0_NEW__DEALLOC_RETURN_NT 399 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF__P0__DEALLOC_RETURN 398 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 397 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF___NOT__P0__DEALLOC_RETURN 396 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0___U2____DEALLOC_RETURN 395 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF__P0_NEW__DEALLOC_RETURN_NT 394 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF__P0__DEALLOC_RETURN 393 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 392 
#define  HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF___NOT__P0__DEALLOC_RETURN 391 
#define  HEX_INS_DUPLEX_RDD___COMBINE___1___U2____DEALLOC_RETURN 390 
#define  HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF__P0_NEW__DEALLOC_RETURN_NT 389 
#define  HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF__P0__DEALLOC_RETURN 388 
#define  HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 387 
#define  HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF___NOT__P0__DEALLOC_RETURN 386 
#define  HEX_INS_DUPLEX_RDD___COMBINE___2___U2____DEALLOC_RETURN 385 
#define  HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF__P0_NEW__DEALLOC_RETURN_NT 384 
#define  HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF__P0__DEALLOC_RETURN 383 
#define  HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 382 
#define  HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF___NOT__P0__DEALLOC_RETURN 381 
#define  HEX_INS_DUPLEX_RDD___COMBINE___3___U2____DEALLOC_RETURN 380 
#define  HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF__P0_NEW__DEALLOC_RETURN_NT 379 
#define  HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF__P0__DEALLOC_RETURN 378 
#define  HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 377 
#define  HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF___NOT__P0__DEALLOC_RETURN 376 
#define  HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____DEALLOC_RETURN 375 
#define  HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF__P0_NEW__DEALLOC_RETURN_NT 374 
#define  HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF__P0__DEALLOC_RETURN 373 
#define  HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 372 
#define  HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF___NOT__P0__DEALLOC_RETURN 371 
#define  HEX_INS_DUPLEX_RD___ADD__RS___1____DEALLOC_RETURN 370 
#define  HEX_INS_DUPLEX_RD___ADD__RS___1____IF__P0_NEW__DEALLOC_RETURN_NT 369 
#define  HEX_INS_DUPLEX_RD___ADD__RS___1____IF__P0__DEALLOC_RETURN 368 
#define  HEX_INS_DUPLEX_RD___ADD__RS___1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 367 
#define  HEX_INS_DUPLEX_RD___ADD__RS___1____IF___NOT__P0__DEALLOC_RETURN 366 
#define  HEX_INS_DUPLEX_RD___ADD__RS____1____DEALLOC_RETURN 365 
#define  HEX_INS_DUPLEX_RD___ADD__RS____1____IF__P0_NEW__DEALLOC_RETURN_NT 364 
#define  HEX_INS_DUPLEX_RD___ADD__RS____1____IF__P0__DEALLOC_RETURN 363 
#define  HEX_INS_DUPLEX_RD___ADD__RS____1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 362 
#define  HEX_INS_DUPLEX_RD___ADD__RS____1____IF___NOT__P0__DEALLOC_RETURN 361 
#define  HEX_INS_DUPLEX_RD___ADD__SP___U6_2____DEALLOC_RETURN 360 
#define  HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF__P0_NEW__DEALLOC_RETURN_NT 359 
#define  HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF__P0__DEALLOC_RETURN 358 
#define  HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 357 
#define  HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF___NOT__P0__DEALLOC_RETURN 356 
#define  HEX_INS_DUPLEX_RD___AND__RS___1____DEALLOC_RETURN 355 
#define  HEX_INS_DUPLEX_RD___AND__RS___1____IF__P0_NEW__DEALLOC_RETURN_NT 354 
#define  HEX_INS_DUPLEX_RD___AND__RS___1____IF__P0__DEALLOC_RETURN 353 
#define  HEX_INS_DUPLEX_RD___AND__RS___1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 352 
#define  HEX_INS_DUPLEX_RD___AND__RS___1____IF___NOT__P0__DEALLOC_RETURN 351 
#define  HEX_INS_DUPLEX_RD___AND__RS___255____DEALLOC_RETURN 350 
#define  HEX_INS_DUPLEX_RD___AND__RS___255____IF__P0_NEW__DEALLOC_RETURN_NT 349 
#define  HEX_INS_DUPLEX_RD___AND__RS___255____IF__P0__DEALLOC_RETURN 348 
#define  HEX_INS_DUPLEX_RD___AND__RS___255____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 347 
#define  HEX_INS_DUPLEX_RD___AND__RS___255____IF___NOT__P0__DEALLOC_RETURN 346 
#define  HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____DEALLOC_RETURN 345 
#define  HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF__P0_NEW__DEALLOC_RETURN_NT 344 
#define  HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF__P0__DEALLOC_RETURN 343 
#define  HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 342 
#define  HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF___NOT__P0__DEALLOC_RETURN 341 
#define  HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____DEALLOC_RETURN 340 
#define  HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF__P0_NEW__DEALLOC_RETURN_NT 339 
#define  HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF__P0__DEALLOC_RETURN 338 
#define  HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 337 
#define  HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF___NOT__P0__DEALLOC_RETURN 336 
#define  HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____DEALLOC_RETURN 335 
#define  HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF__P0_NEW__DEALLOC_RETURN_NT 334 
#define  HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF__P0__DEALLOC_RETURN 333 
#define  HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 332 
#define  HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF___NOT__P0__DEALLOC_RETURN 331 
#define  HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____DEALLOC_RETURN 330 
#define  HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF__P0_NEW__DEALLOC_RETURN_NT 329 
#define  HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF__P0__DEALLOC_RETURN 328 
#define  HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 327 
#define  HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF___NOT__P0__DEALLOC_RETURN 326 
#define  HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____DEALLOC_RETURN 325 
#define  HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF__P0_NEW__DEALLOC_RETURN_NT 324 
#define  HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF__P0__DEALLOC_RETURN 323 
#define  HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 322 
#define  HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF___NOT__P0__DEALLOC_RETURN 321 
#define  HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____DEALLOC_RETURN 320 
#define  HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF__P0_NEW__DEALLOC_RETURN_NT 319 
#define  HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF__P0__DEALLOC_RETURN 318 
#define  HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 317 
#define  HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF___NOT__P0__DEALLOC_RETURN 316 
#define  HEX_INS_DUPLEX_RD___RS___DEALLOC_RETURN 315 
#define  HEX_INS_DUPLEX_RD___RS___IF__P0_NEW__DEALLOC_RETURN_NT 314 
#define  HEX_INS_DUPLEX_RD___RS___IF__P0__DEALLOC_RETURN 313 
#define  HEX_INS_DUPLEX_RD___RS___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 312 
#define  HEX_INS_DUPLEX_RD___RS___IF___NOT__P0__DEALLOC_RETURN 311 
#define  HEX_INS_DUPLEX_RD___SXTB__RS____DEALLOC_RETURN 310 
#define  HEX_INS_DUPLEX_RD___SXTB__RS____IF__P0_NEW__DEALLOC_RETURN_NT 309 
#define  HEX_INS_DUPLEX_RD___SXTB__RS____IF__P0__DEALLOC_RETURN 308 
#define  HEX_INS_DUPLEX_RD___SXTB__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 307 
#define  HEX_INS_DUPLEX_RD___SXTB__RS____IF___NOT__P0__DEALLOC_RETURN 306 
#define  HEX_INS_DUPLEX_RD___SXTH__RS____DEALLOC_RETURN 305 
#define  HEX_INS_DUPLEX_RD___SXTH__RS____IF__P0_NEW__DEALLOC_RETURN_NT 304 
#define  HEX_INS_DUPLEX_RD___SXTH__RS____IF__P0__DEALLOC_RETURN 303 
#define  HEX_INS_DUPLEX_RD___SXTH__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 302 
#define  HEX_INS_DUPLEX_RD___SXTH__RS____IF___NOT__P0__DEALLOC_RETURN 301 
#define  HEX_INS_DUPLEX_RD___ZXTH__RS____DEALLOC_RETURN 300 
#define  HEX_INS_DUPLEX_RD___ZXTH__RS____IF__P0_NEW__DEALLOC_RETURN_NT 299 
#define  HEX_INS_DUPLEX_RD___ZXTH__RS____IF__P0__DEALLOC_RETURN 298 
#define  HEX_INS_DUPLEX_RD___ZXTH__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 297 
#define  HEX_INS_DUPLEX_RD___ZXTH__RS____IF___NOT__P0__DEALLOC_RETURN 296 
#define  HEX_INS_DUPLEX_RD____U6___DEALLOC_RETURN 295 
#define  HEX_INS_DUPLEX_RD____U6___IF__P0_NEW__DEALLOC_RETURN_NT 294 
#define  HEX_INS_DUPLEX_RD____U6___IF__P0__DEALLOC_RETURN 293 
#define  HEX_INS_DUPLEX_RD____U6___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 292 
#define  HEX_INS_DUPLEX_RD____U6___IF___NOT__P0__DEALLOC_RETURN 291 
#define  HEX_INS_DUPLEX_RD_____1___DEALLOC_RETURN 290 
#define  HEX_INS_DUPLEX_RD_____1___IF__P0_NEW__DEALLOC_RETURN_NT 289 
#define  HEX_INS_DUPLEX_RD_____1___IF__P0__DEALLOC_RETURN 288 
#define  HEX_INS_DUPLEX_RD_____1___IF___NOT__P0_NEW__DEALLOC_RETURN_NT 287 
#define  HEX_INS_DUPLEX_RD_____1___IF___NOT__P0__DEALLOC_RETURN 286 
#define  HEX_INS_DUPLEX_RX___ADD__RS__RX____DEALLOC_RETURN 285 
#define  HEX_INS_DUPLEX_RX___ADD__RS__RX____IF__P0_NEW__DEALLOC_RETURN_NT 284 
#define  HEX_INS_DUPLEX_RX___ADD__RS__RX____IF__P0__DEALLOC_RETURN 283 
#define  HEX_INS_DUPLEX_RX___ADD__RS__RX____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 282 
#define  HEX_INS_DUPLEX_RX___ADD__RS__RX____IF___NOT__P0__DEALLOC_RETURN 281 
#define  HEX_INS_DUPLEX_RX___ADD__RX__RS____DEALLOC_RETURN 280 
#define  HEX_INS_DUPLEX_RX___ADD__RX__RS____IF__P0_NEW__DEALLOC_RETURN_NT 279 
#define  HEX_INS_DUPLEX_RX___ADD__RX__RS____IF__P0__DEALLOC_RETURN 278 
#define  HEX_INS_DUPLEX_RX___ADD__RX__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 277 
#define  HEX_INS_DUPLEX_RX___ADD__RX__RS____IF___NOT__P0__DEALLOC_RETURN 276 
#define  HEX_INS_DUPLEX_RX___ADD__RX___S7____DEALLOC_RETURN 275 
#define  HEX_INS_DUPLEX_RX___ADD__RX___S7____IF__P0_NEW__DEALLOC_RETURN_NT 274 
#define  HEX_INS_DUPLEX_RX___ADD__RX___S7____IF__P0__DEALLOC_RETURN 273 
#define  HEX_INS_DUPLEX_RX___ADD__RX___S7____IF___NOT__P0_NEW__DEALLOC_RETURN_NT 272 
#define  HEX_INS_DUPLEX_RX___ADD__RX___S7____IF___NOT__P0__DEALLOC_RETURN 271 
#define  HEX_INS_IF__CMP_EQ__NS_NEW__RT___JUMP_NT__R9_2 270 
#define  HEX_INS_IF__CMP_EQ__NS_NEW__RT___JUMP_T__R9_2 269 
#define  HEX_INS_IF__CMP_EQ__NS_NEW___U5___JUMP_NT__R9_2 268 
#define  HEX_INS_IF__CMP_EQ__NS_NEW___U5___JUMP_T__R9_2 267 
#define  HEX_INS_IF__CMP_EQ__NS_NEW____1___JUMP_NT__R9_2 266 
#define  HEX_INS_IF__CMP_EQ__NS_NEW____1___JUMP_T__R9_2 265 
#define  HEX_INS_IF__CMP_GTU__NS_NEW__RT___JUMP_NT__R9_2 264 
#define  HEX_INS_IF__CMP_GTU__NS_NEW__RT___JUMP_T__R9_2 263 
#define  HEX_INS_IF__CMP_GTU__NS_NEW___U5___JUMP_NT__R9_2 262 
#define  HEX_INS_IF__CMP_GTU__NS_NEW___U5___JUMP_T__R9_2 261 
#define  HEX_INS_IF__CMP_GTU__RT__NS_NEW___JUMP_NT__R9_2 260 
#define  HEX_INS_IF__CMP_GTU__RT__NS_NEW___JUMP_T__R9_2 259 
#define  HEX_INS_IF__CMP_GT__NS_NEW__RT___JUMP_NT__R9_2 258 
#define  HEX_INS_IF__CMP_GT__NS_NEW__RT___JUMP_T__R9_2 257 
#define  HEX_INS_IF__CMP_GT__NS_NEW___U5___JUMP_NT__R9_2 256 
#define  HEX_INS_IF__CMP_GT__NS_NEW___U5___JUMP_T__R9_2 255 
#define  HEX_INS_IF__CMP_GT__NS_NEW____1___JUMP_NT__R9_2 254 
#define  HEX_INS_IF__CMP_GT__NS_NEW____1___JUMP_T__R9_2 253 
#define  HEX_INS_IF__CMP_GT__RT__NS_NEW___JUMP_NT__R9_2 252 
#define  HEX_INS_IF__CMP_GT__RT__NS_NEW___JUMP_T__R9_2 251 
#define  HEX_INS_IF__NOT_PS_DEALLOC_RETURN 250 
#define  HEX_INS_IF__NOT_PS_NEW_DEALLOC_RETURN_NT 249 
#define  HEX_INS_IF__NOT_PS_NEW_DEALLOC_RETURN_T 248 
#define  HEX_INS_IF__NOT_PU_CALL__R15_2 247 
#define  HEX_INS_IF__NOT_PU_JUMP_NT__R15_2 246 
#define  HEX_INS_IF__NOT_PU_JUMP_T__R15_2 245 
#define  HEX_INS_IF__NOT_PU_NEW_JUMP_NT__R15_2 244 
#define  HEX_INS_IF__NOT_PU_NEW_JUMP_T__R15_2 243 
#define  HEX_INS_IF__PS_NEW__DEALLOC_RETURN_NT 242 
#define  HEX_INS_IF__PS_NEW__DEALLOC_RETURN_T 241 
#define  HEX_INS_IF__PS__DEALLOC_RETURN 240 
#define  HEX_INS_IF__PU_NEW__JUMP_NT__R15_2 239 
#define  HEX_INS_IF__PU_NEW__JUMP_T__R15_2 238 
#define  HEX_INS_IF__PU__CALL__R15_2 237 
#define  HEX_INS_IF__PU__JUMP_NT__R15_2 236 
#define  HEX_INS_IF__PU__JUMP_T__R15_2 235 
#define  HEX_INS_IF__RS_GT_EQ___0__JUMP_NT__R13_2 234 
#define  HEX_INS_IF__RS_GT_EQ___0__JUMP_T__R13_2 233 
#define  HEX_INS_IF__RS_LT_EQ___0__JUMP_NT__R13_2 232 
#define  HEX_INS_IF__RS_LT_EQ___0__JUMP_T__R13_2 231 
#define  HEX_INS_IF__RS__EQ___0__JUMP_NT__R13_2 230 
#define  HEX_INS_IF__RS__EQ___0__JUMP_T__R13_2 229 
#define  HEX_INS_IF__RS__NOT____0__JUMP_NT__R13_2 228 
#define  HEX_INS_IF__RS__NOT____0__JUMP_T__R13_2 227 
#define  HEX_INS_IF__TSTBIT__NS_NEW___0___JUMP_NT__R9_2 226 
#define  HEX_INS_IF__TSTBIT__NS_NEW___0___JUMP_T__R9_2 225 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW__RT___JUMP_NT__R9_2 224 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW__RT___JUMP_T__R9_2 223 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW___U5___JUMP_NT__R9_2 222 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW___U5___JUMP_T__R9_2 221 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW____1___JUMP_NT__R9_2 220 
#define  HEX_INS_IF___NOT_CMP_EQ__NS_NEW____1___JUMP_T__R9_2 219 
#define  HEX_INS_IF___NOT_CMP_GTU__NS_NEW__RT___JUMP_NT__R9_2 218 
#define  HEX_INS_IF___NOT_CMP_GTU__NS_NEW__RT___JUMP_T__R9_2 217 
#define  HEX_INS_IF___NOT_CMP_GTU__NS_NEW___U5___JUMP_NT__R9_2 216 
#define  HEX_INS_IF___NOT_CMP_GTU__NS_NEW___U5___JUMP_T__R9_2 215 
#define  HEX_INS_IF___NOT_CMP_GTU__RT__NS_NEW___JUMP_NT__R9_2 214 
#define  HEX_INS_IF___NOT_CMP_GTU__RT__NS_NEW___JUMP_T__R9_2 213 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW__RT___JUMP_NT__R9_2 212 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW__RT___JUMP_T__R9_2 211 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW___U5___JUMP_NT__R9_2 210 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW___U5___JUMP_T__R9_2 209 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW____1___JUMP_NT__R9_2 208 
#define  HEX_INS_IF___NOT_CMP_GT__NS_NEW____1___JUMP_T__R9_2 207 
#define  HEX_INS_IF___NOT_CMP_GT__RT__NS_NEW___JUMP_NT__R9_2 206 
#define  HEX_INS_IF___NOT_CMP_GT__RT__NS_NEW___JUMP_T__R9_2 205 
#define  HEX_INS_IF___NOT_TSTBIT__NS_NEW___0___JUMP_NT__R9_2 204 
#define  HEX_INS_IF___NOT_TSTBIT__NS_NEW___0___JUMP_T__R9_2 203 
#define  HEX_INS_JUMP__R22_2 202 
#define  HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF__P0_NEW__JUMP_NT__R9_2 201 
#define  HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF__P0_NEW__JUMP_T__R9_2 200 
#define  HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2 199 
#define  HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2 198 
#define  HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF__P0_NEW__JUMP_NT__R9_2 197 
#define  HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF__P0_NEW__JUMP_T__R9_2 196 
#define  HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2 195 
#define  HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2 194 
#define  HEX_INS_MULT_P0___CMP_EQ__RS____1____IF__P0_NEW__JUMP_NT__R9_2 193 
#define  HEX_INS_MULT_P0___CMP_EQ__RS____1____IF__P0_NEW__JUMP_T__R9_2 192 
#define  HEX_INS_MULT_P0___CMP_EQ__RS____1____IF___NOT_P0_NEW__JUMP_NT__R9_2 191 
#define  HEX_INS_MULT_P0___CMP_EQ__RS____1____IF___NOT_P0_NEW__JUMP_T__R9_2 190 
#define  HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF__P0_NEW__JUMP_NT__R9_2 189 
#define  HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF__P0_NEW__JUMP_T__R9_2 188 
#define  HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2 187 
#define  HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2 186 
#define  HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF__P0_NEW__JUMP_NT__R9_2 185 
#define  HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF__P0_NEW__JUMP_T__R9_2 184 
#define  HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2 183 
#define  HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2 182 
#define  HEX_INS_MULT_P0___CMP_GT__RS__RT____IF__P0_NEW__JUMP_NT__R9_2 181 
#define  HEX_INS_MULT_P0___CMP_GT__RS__RT____IF__P0_NEW__JUMP_T__R9_2 180 
#define  HEX_INS_MULT_P0___CMP_GT__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2 179 
#define  HEX_INS_MULT_P0___CMP_GT__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2 178 
#define  HEX_INS_MULT_P0___CMP_GT__RS___U5____IF__P0_NEW__JUMP_NT__R9_2 177 
#define  HEX_INS_MULT_P0___CMP_GT__RS___U5____IF__P0_NEW__JUMP_T__R9_2 176 
#define  HEX_INS_MULT_P0___CMP_GT__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2 175 
#define  HEX_INS_MULT_P0___CMP_GT__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2 174 
#define  HEX_INS_MULT_P0___CMP_GT__RS____1____IF__P0_NEW__JUMP_NT__R9_2 173 
#define  HEX_INS_MULT_P0___CMP_GT__RS____1____IF__P0_NEW__JUMP_T__R9_2 172 
#define  HEX_INS_MULT_P0___CMP_GT__RS____1____IF___NOT_P0_NEW__JUMP_NT__R9_2 171 
#define  HEX_INS_MULT_P0___CMP_GT__RS____1____IF___NOT_P0_NEW__JUMP_T__R9_2 170 
#define  HEX_INS_MULT_P0___TSTBIT__RS___0____IF__P0_NEW__JUMP_NT__R9_2 169 
#define  HEX_INS_MULT_P0___TSTBIT__RS___0____IF__P0_NEW__JUMP_T__R9_2 168 
#define  HEX_INS_MULT_P0___TSTBIT__RS___0____IF___NOT_P0_NEW__JUMP_NT__R9_2 167 
#define  HEX_INS_MULT_P0___TSTBIT__RS___0____IF___NOT_P0_NEW__JUMP_T__R9_2 166 
#define  HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF__P1_NEW__JUMP_NT__R9_2 165 
#define  HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF__P1_NEW__JUMP_T__R9_2 164 
#define  HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2 163 
#define  HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2 162 
#define  HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF__P1_NEW__JUMP_NT__R9_2 161 
#define  HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF__P1_NEW__JUMP_T__R9_2 160 
#define  HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2 159 
#define  HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2 158 
#define  HEX_INS_MULT_P1___CMP_EQ__RS____1____IF__P1_NEW__JUMP_NT__R9_2 157 
#define  HEX_INS_MULT_P1___CMP_EQ__RS____1____IF__P1_NEW__JUMP_T__R9_2 156 
#define  HEX_INS_MULT_P1___CMP_EQ__RS____1____IF___NOT_P1_NEW__JUMP_NT__R9_2 155 
#define  HEX_INS_MULT_P1___CMP_EQ__RS____1____IF___NOT_P1_NEW__JUMP_T__R9_2 154 
#define  HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF__P1_NEW__JUMP_NT__R9_2 153 
#define  HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF__P1_NEW__JUMP_T__R9_2 152 
#define  HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2 151 
#define  HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2 150 
#define  HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF__P1_NEW__JUMP_NT__R9_2 149 
#define  HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF__P1_NEW__JUMP_T__R9_2 148 
#define  HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2 147 
#define  HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2 146 
#define  HEX_INS_MULT_P1___CMP_GT__RS__RT____IF__P1_NEW__JUMP_NT__R9_2 145 
#define  HEX_INS_MULT_P1___CMP_GT__RS__RT____IF__P1_NEW__JUMP_T__R9_2 144 
#define  HEX_INS_MULT_P1___CMP_GT__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2 143 
#define  HEX_INS_MULT_P1___CMP_GT__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2 142 
#define  HEX_INS_MULT_P1___CMP_GT__RS___U5____IF__P1_NEW__JUMP_NT__R9_2 141 
#define  HEX_INS_MULT_P1___CMP_GT__RS___U5____IF__P1_NEW__JUMP_T__R9_2 140 
#define  HEX_INS_MULT_P1___CMP_GT__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2 139 
#define  HEX_INS_MULT_P1___CMP_GT__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2 138 
#define  HEX_INS_MULT_P1___CMP_GT__RS____1____IF__P1_NEW__JUMP_NT__R9_2 137 
#define  HEX_INS_MULT_P1___CMP_GT__RS____1____IF__P1_NEW__JUMP_T__R9_2 136 
#define  HEX_INS_MULT_P1___CMP_GT__RS____1____IF___NOT_P1_NEW__JUMP_NT__R9_2 135 
#define  HEX_INS_MULT_P1___CMP_GT__RS____1____IF___NOT_P1_NEW__JUMP_T__R9_2 134 
#define  HEX_INS_MULT_P1___TSTBIT__RS___0____IF__P1_NEW__JUMP_NT__R9_2 133 
#define  HEX_INS_MULT_P1___TSTBIT__RS___0____IF__P1_NEW__JUMP_T__R9_2 132 
#define  HEX_INS_MULT_P1___TSTBIT__RS___0____IF___NOT_P1_NEW__JUMP_NT__R9_2 131 
#define  HEX_INS_MULT_P1___TSTBIT__RS___0____IF___NOT_P1_NEW__JUMP_T__R9_2 130 
#define  HEX_INS_MULT_RD___RS___JUMP__R9_2 129 
#define  HEX_INS_MULT_RD____U6___JUMP__R9_2 128 
 void* R_ANAL_OP_TYPE_CALL ; 
 void* R_ANAL_OP_TYPE_CJMP ; 
 void* R_ANAL_OP_TYPE_JMP ; 
 void* R_ANAL_OP_TYPE_RET ; 

int hexagon_anal_instruction(HexInsn *hi, RAnalOp *op) {
	switch (hi->instruction) {
	case HEX_INS_CALL__R22_2: {
		// call #r22:2
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = op->addr + hi->ops[0].op.imm;
		break;
	}
	case HEX_INS_IF__PU__CALL__R15_2: {
		// if (Pu) call #r15:2
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = op->addr + hi->ops[1].op.imm;
		break;
	}
	case HEX_INS_IF__NOT_PU_CALL__R15_2: {
		// if !Pu call #r15:2
		op->type = R_ANAL_OP_TYPE_CALL;
		op->jump = op->addr + hi->ops[1].op.imm;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS____1____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, #-1) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS____1____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, #-1) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___TSTBIT__RS___0____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = tstbit (Rs, #0) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS____1____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, #-1) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS____1____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, #-1) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___TSTBIT__RS___0____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = tstbit (Rs, #0) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS____1____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, #-1) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS____1____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, #-1) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___TSTBIT__RS___0____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = tstbit (Rs, #0) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS____1____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, #-1) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS____1____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, #-1) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___TSTBIT__RS___0____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = tstbit (Rs, #0) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, #U5) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, #U5) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, #U5) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, #U5) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS___U5____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, #U5) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS___U5____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, #U5) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, #U5) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, #U5) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gtu (Rs, #U5) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gtu (Rs, #U5) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gtu (Rs, #U5) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS___U5____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gtu (Rs, #U5) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS____1____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, #-1) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS____1____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, #-1) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___TSTBIT__RS___0____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = tstbit (Rs, #0) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS____1____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, #-1) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS____1____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, #-1) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___TSTBIT__RS___0____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = tstbit (Rs, #0) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS____1____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, #-1) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS____1____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, #-1) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___TSTBIT__RS___0____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = tstbit (Rs, #0) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS____1____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, #-1) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS____1____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, #-1) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___TSTBIT__RS___0____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = tstbit (Rs, #0) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, #U5) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, #U5) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, #U5) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, #U5) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS___U5____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, #U5) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS___U5____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, #U5) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, #U5) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, #U5) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gtu (Rs, #U5) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gtu (Rs, #U5) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gtu (Rs, #U5) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS___U5____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gtu (Rs, #U5) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, Rt) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, Rt) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, Rt) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, Rt) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.eq (Rs, Rt) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.eq (Rs, Rt) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_EQ__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.eq (Rs, Rt) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_EQ__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.eq (Rs, Rt) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS__RT____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, Rt) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS__RT____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, Rt) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS__RT____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, Rt) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS__RT____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, Rt) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gt (Rs, Rt) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gt (Rs, Rt) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GT__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gt (Rs, Rt) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GT__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gt (Rs, Rt) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF__P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gtu (Rs, Rt) ; if (p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF__P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gtu (Rs, Rt) ; if (p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF__P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gtu (Rs, Rt) ; if (p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF__P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gtu (Rs, Rt) ; if (p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF___NOT_P0_NEW__JUMP_NT__R9_2: {
		// p0 = cmp.gtu (Rs, Rt) ; if (!p0.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF___NOT_P1_NEW__JUMP_NT__R9_2: {
		// p1 = cmp.gtu (Rs, Rt) ; if (!p1.new) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P0___CMP_GTU__RS__RT____IF___NOT_P0_NEW__JUMP_T__R9_2: {
		// p0 = cmp.gtu (Rs, Rt) ; if (!p0.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_P1___CMP_GTU__RS__RT____IF___NOT_P1_NEW__JUMP_T__R9_2: {
		// p1 = cmp.gtu (Rs, Rt) ; if (!p1.new) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_JUMP__R22_2: {
		// jump #r22:2
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = hi->ops[0].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__PU__JUMP_NT__R15_2: {
		// if (Pu) jump:nt #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__PU__JUMP_T__R15_2: {
		// if (Pu) jump:t #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__NOT_PU_JUMP_NT__R15_2: {
		// if !Pu jump:nt #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__NOT_PU_JUMP_T__R15_2: {
		// if !Pu jump:t #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__PU_NEW__JUMP_NT__R15_2: {
		// if (Pu.new) jump:nt #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__PU_NEW__JUMP_T__R15_2: {
		// if (Pu.new) jump:t #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__NOT_PU_NEW_JUMP_NT__R15_2: {
		// if !Pu.new jump:nt #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__NOT_PU_NEW_JUMP_T__R15_2: {
		// if !Pu.new jump:t #r15:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS__NOT____0__JUMP_NT__R13_2: {
		// if (Rs != #0) jump:nt #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS__NOT____0__JUMP_T__R13_2: {
		// if (Rs != #0) jump:t #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS_GT_EQ___0__JUMP_NT__R13_2: {
		// if (Rs> = #0) jump:nt #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS_GT_EQ___0__JUMP_T__R13_2: {
		// if (Rs> = #0) jump:t #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS__EQ___0__JUMP_NT__R13_2: {
		// if (Rs == #0) jump:nt #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS__EQ___0__JUMP_T__R13_2: {
		// if (Rs == #0) jump:t #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS_LT_EQ___0__JUMP_NT__R13_2: {
		// if (Rs< = #0) jump:nt #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__RS_LT_EQ___0__JUMP_T__R13_2: {
		// if (Rs< = #0) jump:t #r13:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_RD____U6___JUMP__R9_2: {
		// Rd = #U6 ; jump #r9:2
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_MULT_RD___RS___JUMP__R9_2: {
		// Rd = Rs ; jump #r9:2
		op->type = R_ANAL_OP_TYPE_JMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_DEALLOC_RETURN: {
		// dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__PS_NEW__DEALLOC_RETURN_NT: {
		// if (Ps.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__PS__DEALLOC_RETURN: {
		// if (Ps) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__PS_NEW__DEALLOC_RETURN_T: {
		// if (Ps.new) dealloc_return:t
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__NOT_PS_NEW_DEALLOC_RETURN_NT: {
		// if !Ps.new dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__NOT_PS_DEALLOC_RETURN: {
		// if !Ps dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__NOT_PS_NEW_DEALLOC_RETURN_T: {
		// if !Ps.new dealloc_return:t
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (cmp.eq (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW__RT___JUMP_T__R9_2: {
		// if (cmp.eq (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (!cmp.eq (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW__RT___JUMP_T__R9_2: {
		// if (!cmp.eq (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (cmp.gt (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW__RT___JUMP_T__R9_2: {
		// if (cmp.gt (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (!cmp.gt (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW__RT___JUMP_T__R9_2: {
		// if (!cmp.gt (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (cmp.gtu (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__NS_NEW__RT___JUMP_T__R9_2: {
		// if (cmp.gtu (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__NS_NEW__RT___JUMP_NT__R9_2: {
		// if (!cmp.gtu (Ns.new, Rt)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__NS_NEW__RT___JUMP_T__R9_2: {
		// if (!cmp.gtu (Ns.new, Rt)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__RT__NS_NEW___JUMP_NT__R9_2: {
		// if (cmp.gt (Rt, Ns.new)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__RT__NS_NEW___JUMP_T__R9_2: {
		// if (cmp.gt (Rt, Ns.new)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__RT__NS_NEW___JUMP_NT__R9_2: {
		// if (!cmp.gt (Rt, Ns.new)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__RT__NS_NEW___JUMP_T__R9_2: {
		// if (!cmp.gt (Rt, Ns.new)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__RT__NS_NEW___JUMP_NT__R9_2: {
		// if (cmp.gtu (Rt, Ns.new)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__RT__NS_NEW___JUMP_T__R9_2: {
		// if (cmp.gtu (Rt, Ns.new)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__RT__NS_NEW___JUMP_NT__R9_2: {
		// if (!cmp.gtu (Rt, Ns.new)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__RT__NS_NEW___JUMP_T__R9_2: {
		// if (!cmp.gtu (Rt, Ns.new)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (cmp.eq (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW___U5___JUMP_T__R9_2: {
		// if (cmp.eq (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (!cmp.eq (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW___U5___JUMP_T__R9_2: {
		// if (!cmp.eq (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (cmp.gt (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW___U5___JUMP_T__R9_2: {
		// if (cmp.gt (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (!cmp.gt (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW___U5___JUMP_T__R9_2: {
		// if (!cmp.gt (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (cmp.gtu (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GTU__NS_NEW___U5___JUMP_T__R9_2: {
		// if (cmp.gtu (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__NS_NEW___U5___JUMP_NT__R9_2: {
		// if (!cmp.gtu (Ns.new, #U5)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GTU__NS_NEW___U5___JUMP_T__R9_2: {
		// if (!cmp.gtu (Ns.new, #U5)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[2].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__TSTBIT__NS_NEW___0___JUMP_NT__R9_2: {
		// if (tstbit (Ns.new, #0)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__TSTBIT__NS_NEW___0___JUMP_T__R9_2: {
		// if (tstbit (Ns.new, #0)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_TSTBIT__NS_NEW___0___JUMP_NT__R9_2: {
		// if (!tstbit (Ns.new, #0)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_TSTBIT__NS_NEW___0___JUMP_T__R9_2: {
		// if (!tstbit (Ns.new, #0)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW____1___JUMP_NT__R9_2: {
		// if (cmp.eq (Ns.new, #-1)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_EQ__NS_NEW____1___JUMP_T__R9_2: {
		// if (cmp.eq (Ns.new, #-1)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW____1___JUMP_NT__R9_2: {
		// if (!cmp.eq (Ns.new, #-1)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_EQ__NS_NEW____1___JUMP_T__R9_2: {
		// if (!cmp.eq (Ns.new, #-1)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW____1___JUMP_NT__R9_2: {
		// if (cmp.gt (Ns.new, #-1)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF__CMP_GT__NS_NEW____1___JUMP_T__R9_2: {
		// if (cmp.gt (Ns.new, #-1)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW____1___JUMP_NT__R9_2: {
		// if (!cmp.gt (Ns.new, #-1)) jump:nt #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_IF___NOT_CMP_GT__NS_NEW____1___JUMP_T__R9_2: {
		// if (!cmp.gt (Ns.new, #-1)) jump:t #r9:2
		op->type = R_ANAL_OP_TYPE_CJMP;
		op->jump = hi->ops[1].op.imm;
		op->fail = op->addr + op->size;
		break;
	}
	case HEX_INS_DUPLEX_RD_____1___DEALLOC_RETURN: {
		// Rd = #-1 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD_____1___IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = #-1 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD_____1___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = #-1 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD_____1___IF__P0__DEALLOC_RETURN: {
		// Rd = #-1 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD_____1___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = #-1 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD____U6___DEALLOC_RETURN: {
		// Rd = #u6 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD____U6___IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = #u6 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD____U6___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = #u6 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD____U6___IF__P0__DEALLOC_RETURN: {
		// Rd = #u6 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD____U6___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = #u6 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___RS___DEALLOC_RETURN: {
		// Rd = Rs ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___RS___IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = Rs ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___RS___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = Rs ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___RS___IF__P0__DEALLOC_RETURN: {
		// Rd = Rs ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___RS___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = Rs ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS____1____DEALLOC_RETURN: {
		// Rd = add (Rs, #-1) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS____1____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = add (Rs, #-1) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS____1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Rs, #-1) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS____1____IF__P0__DEALLOC_RETURN: {
		// Rd = add (Rs, #-1) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS____1____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Rs, #-1) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS___1____DEALLOC_RETURN: {
		// Rd = add (Rs, #1) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS___1____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = add (Rs, #1) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS___1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Rs, #1) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS___1____IF__P0__DEALLOC_RETURN: {
		// Rd = add (Rs, #1) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__RS___1____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Rs, #1) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__SP___U6_2____DEALLOC_RETURN: {
		// Rd = add (Sp, #u6:2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = add (Sp, #u6:2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Sp, #u6:2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF__P0__DEALLOC_RETURN: {
		// Rd = add (Sp, #u6:2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ADD__SP___U6_2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = add (Sp, #u6:2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___1____DEALLOC_RETURN: {
		// Rd = and (Rs, #1) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___1____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = and (Rs, #1) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = and (Rs, #1) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___1____IF__P0__DEALLOC_RETURN: {
		// Rd = and (Rs, #1) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___1____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = and (Rs, #1) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___255____DEALLOC_RETURN: {
		// Rd = and (Rs, #255) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___255____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = and (Rs, #255) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___255____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = and (Rs, #255) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___255____IF__P0__DEALLOC_RETURN: {
		// Rd = and (Rs, #255) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___AND__RS___255____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = and (Rs, #255) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____DEALLOC_RETURN: {
		// Rd = memb (Rs + #u3:0) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memb (Rs + #u3:0) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memb (Rs + #u3:0) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF__P0__DEALLOC_RETURN: {
		// Rd = memb (Rs + #u3:0) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMB__RS____U3_0____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memb (Rs + #u3:0) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____DEALLOC_RETURN: {
		// Rd = memh (Rs + #u3:1) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memh (Rs + #u3:1) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memh (Rs + #u3:1) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF__P0__DEALLOC_RETURN: {
		// Rd = memh (Rs + #u3:1) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMH__RS____U3_1____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memh (Rs + #u3:1) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____DEALLOC_RETURN: {
		// Rd = memub (Rs + #u4:0) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memub (Rs + #u4:0) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memub (Rs + #u4:0) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF__P0__DEALLOC_RETURN: {
		// Rd = memub (Rs + #u4:0) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUB__RS____U4_0____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memub (Rs + #u4:0) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____DEALLOC_RETURN: {
		// Rd = memuh (Rs + #u3:1) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memuh (Rs + #u3:1) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memuh (Rs + #u3:1) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF__P0__DEALLOC_RETURN: {
		// Rd = memuh (Rs + #u3:1) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMUH__RS____U3_1____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memuh (Rs + #u3:1) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____DEALLOC_RETURN: {
		// Rd = memw (Rs + #u4:2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memw (Rs + #u4:2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memw (Rs + #u4:2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF__P0__DEALLOC_RETURN: {
		// Rd = memw (Rs + #u4:2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__RS____U4_2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memw (Rs + #u4:2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____DEALLOC_RETURN: {
		// Rd = memw (Sp + #u5:2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = memw (Sp + #u5:2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memw (Sp + #u5:2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF__P0__DEALLOC_RETURN: {
		// Rd = memw (Sp + #u5:2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___MEMW__SP____U5_2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = memw (Sp + #u5:2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTB__RS____DEALLOC_RETURN: {
		// Rd = sxtb (Rs) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTB__RS____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = sxtb (Rs) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTB__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = sxtb (Rs) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTB__RS____IF__P0__DEALLOC_RETURN: {
		// Rd = sxtb (Rs) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTB__RS____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = sxtb (Rs) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTH__RS____DEALLOC_RETURN: {
		// Rd = sxth (Rs) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTH__RS____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = sxth (Rs) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTH__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = sxth (Rs) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTH__RS____IF__P0__DEALLOC_RETURN: {
		// Rd = sxth (Rs) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___SXTH__RS____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = sxth (Rs) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ZXTH__RS____DEALLOC_RETURN: {
		// Rd = zxth (Rs) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ZXTH__RS____IF___NOT__P0__DEALLOC_RETURN: {
		// Rd = zxth (Rs) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ZXTH__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = zxth (Rs) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ZXTH__RS____IF__P0__DEALLOC_RETURN: {
		// Rd = zxth (Rs) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RD___ZXTH__RS____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rd = zxth (Rs) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0___U2____DEALLOC_RETURN: {
		// Rdd = combine (#0, #u2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (#0, #u2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#0, #u2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (#0, #u2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0___U2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#0, #u2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0__RS____DEALLOC_RETURN: {
		// Rdd = combine (#0, Rs) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (#0, Rs) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#0, Rs) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (#0, Rs) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___0__RS____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#0, Rs) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___1___U2____DEALLOC_RETURN: {
		// Rdd = combine (#1, #u2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (#1, #u2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#1, #u2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (#1, #u2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___1___U2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#1, #u2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___2___U2____DEALLOC_RETURN: {
		// Rdd = combine (#2, #u2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (#2, #u2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#2, #u2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (#2, #u2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___2___U2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#2, #u2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___3___U2____DEALLOC_RETURN: {
		// Rdd = combine (#3, #u2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (#3, #u2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#3, #u2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (#3, #u2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE___3___U2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (#3, #u2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE__RS___0____DEALLOC_RETURN: {
		// Rdd = combine (Rs, #0) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = combine (Rs, #0) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (Rs, #0) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF__P0__DEALLOC_RETURN: {
		// Rdd = combine (Rs, #0) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___COMBINE__RS___0____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = combine (Rs, #0) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____DEALLOC_RETURN: {
		// Rdd = memd (Sp + #u5:3) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF___NOT__P0__DEALLOC_RETURN: {
		// Rdd = memd (Sp + #u5:3) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = memd (Sp + #u5:3) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF__P0__DEALLOC_RETURN: {
		// Rdd = memd (Sp + #u5:3) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RDD___MEMD__SP____U5_3____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rdd = memd (Sp + #u5:3) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RS__RX____DEALLOC_RETURN: {
		// Rx = add (Rs, Rx) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RS__RX____IF___NOT__P0__DEALLOC_RETURN: {
		// Rx = add (Rs, Rx) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RS__RX____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rs, Rx) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RS__RX____IF__P0__DEALLOC_RETURN: {
		// Rx = add (Rs, Rx) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RS__RX____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rs, Rx) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX___S7____DEALLOC_RETURN: {
		// Rx = add (Rx, #s7) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX___S7____IF___NOT__P0__DEALLOC_RETURN: {
		// Rx = add (Rx, #s7) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX___S7____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rx, #s7) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX___S7____IF__P0__DEALLOC_RETURN: {
		// Rx = add (Rx, #s7) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX___S7____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rx, #s7) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX__RS____DEALLOC_RETURN: {
		// Rx = add (Rx, Rs) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX__RS____IF___NOT__P0__DEALLOC_RETURN: {
		// Rx = add (Rx, Rs) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX__RS____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rx, Rs) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX__RS____IF__P0__DEALLOC_RETURN: {
		// Rx = add (Rx, Rs) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_RX___ADD__RX__RS____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// Rx = add (Rx, Rs) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0__RD____0___DEALLOC_RETURN: {
		// if (! p0) Rd = #0 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF___NOT__P0__DEALLOC_RETURN: {
		// if (! p0) Rd = #0 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// if (! p0) Rd = #0 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF__P0__DEALLOC_RETURN: {
		// if (! p0) Rd = #0 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// if (! p0) Rd = #0 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___DEALLOC_RETURN: {
		// if (! p0.new) Rd = #0 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF___NOT__P0__DEALLOC_RETURN: {
		// if (! p0.new) Rd = #0 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// if (! p0.new) Rd = #0 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF__P0__DEALLOC_RETURN: {
		// if (! p0.new) Rd = #0 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF___NOT__P0_NEW__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// if (! p0.new) Rd = #0 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0__RD____0___DEALLOC_RETURN: {
		// if (p0) Rd = #0 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0__RD____0___IF___NOT__P0__DEALLOC_RETURN: {
		// if (p0) Rd = #0 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// if (p0) Rd = #0 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0__RD____0___IF__P0__DEALLOC_RETURN: {
		// if (p0) Rd = #0 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// if (p0) Rd = #0 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0_NEW__RD____0___DEALLOC_RETURN: {
		// if (p0.new) Rd = #0 ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF___NOT__P0__DEALLOC_RETURN: {
		// if (p0.new) Rd = #0 ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// if (p0.new) Rd = #0 ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF__P0__DEALLOC_RETURN: {
		// if (p0.new) Rd = #0 ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_IF__P0_NEW__RD____0___IF__P0_NEW__DEALLOC_RETURN_NT: {
		// if (p0.new) Rd = #0 ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____DEALLOC_RETURN: {
		// p0 = cmp.eq (Rs, #u2) ; dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF___NOT__P0__DEALLOC_RETURN: {
		// p0 = cmp.eq (Rs, #u2) ; if (! p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF___NOT__P0_NEW__DEALLOC_RETURN_NT: {
		// p0 = cmp.eq (Rs, #u2) ; if (! p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF__P0__DEALLOC_RETURN: {
		// p0 = cmp.eq (Rs, #u2) ; if (p0) dealloc_return
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	case HEX_INS_DUPLEX_P0___CMP_EQ__RS___U2____IF__P0_NEW__DEALLOC_RETURN_NT: {
		// p0 = cmp.eq (Rs, #u2) ; if (p0.new) dealloc_return:nt
		op->type = R_ANAL_OP_TYPE_RET;
		break;
	}
	}
	return op->size;
}